/*-
 * Copyright (c) 2010 Ermal Lu�i <eri@pfsense.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


/* 
 * The parsing code is taken from dnsmasq isc.c file and modified to work
 * in this code. 
 */
/* dnsmasq is Copyright (c) 2000-2007 Simon Kelley

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 dated June, 1991, or
   (at your option) version 3 dated 29 June, 2007.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/* Code in this file is based on contributions by John Volpe. */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/queue.h>

#include <netinet/in.h>
#include <arpa/nameser.h>
#include <arpa/inet.h>

#include <syslog.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>

#define _WITH_DPRINTF
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <errno.h>

#define MAXTOK 64
#define PIDFILE	"/var/run/dhcpleases.pid"

struct isc_lease {
	char *name, *fqdn;
	time_t expires;
	struct in_addr addr;
	LIST_ENTRY(isc_lease) next;
};

LIST_HEAD(isc_leases, isc_lease) leases =
	LIST_HEAD_INITIALIZER(leases);
static char *leasefile = NULL;
static char *pidfile = NULL;
static char *HOSTS = NULL;
static FILE *fp = NULL;
static char *domain_suffix = NULL;
static char *command = NULL;
static size_t hostssize = 0;
static size_t foreground = 0;

static int fexist(char *);
static int fsize(char *);
static int legal_char(char);
static int canonicalise(char *);
static int hostname_isequal(char *, char *);
static int next_token (char *, int, FILE *);
static time_t convert_time(struct tm);
static int load_dhcp(time_t);

static int write_status(void);
static void cleanup(void);
static void signal_process(void);
static void handle_signal(int);

/* Check if file exists */
static int
fexist(char * filename)
{
        struct stat buf;

        if (( stat (filename, &buf)) < 0)
                return (0);

        if (! S_ISREG(buf.st_mode))
                return (0);

        return(1);
}

static int
fsize(char * filename)
{
        struct stat buf;

        if (( stat (filename, &buf)) < 0)
                return (-1);

        if (! S_ISREG(buf.st_mode))
                return (-1);

        return(buf.st_size);
}

/*
 * check for legal char a-z A-Z 0-9 -
 * (also / , used for RFC2317 and _ used in windows queries
 * and space, for DNS-SD stuff)
 */
static int
legal_char(char c) {
	if ((c >= 'A' && c <= 'Z') ||
	    (c >= 'a' && c <= 'z') ||
	    (c >= '0' && c <= '9') ||
	    c == '-' || c == '/' || c == '_' || c == ' ')
		return (1);
	return (0);
}

/*
 * check for legal chars and remove trailing .
 * also fail empty string and label > 63 chars
 */
static int
canonicalise(char *s) {
	size_t dotgap = 0, l = strlen(s);
	char c;
	int nowhite = 0;

	if (l == 0 || l > MAXDNAME)
		return (0);

	if (s[l-1] == '.') {
		if (l == 1)
			return (0);
		s[l-1] = 0;
	}

	while ((c = *s)) {
		if (c == '.')
			dotgap = 0;
		else if (!legal_char(c) || (++dotgap > MAXLABEL))
			return (0);
		else if (c != ' ')
			nowhite = 1;
		s++;
	}

	return (nowhite);
}

/* don't use strcasecmp and friends here - they may be messed up by LOCALE */
static int
hostname_isequal(char *a, char *b) {
	unsigned int c1, c2;

	do {
		c1 = (unsigned char) *a++;
		c2 = (unsigned char) *b++;

		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 'a' - 'A';
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 'a' - 'A';

		if (c1 != c2)
			return 0;
	} while (c1);

	return (1);
}

static int
next_token (char *token, int buffsize, FILE * fp)
{
	int c, count = 0;
	char *cp = token;

	while((c = getc(fp)) != EOF) {
		if (c == '#')
			do {
				c = getc(fp);
			} while (c != '\n' && c != EOF);

		if (c == ' ' || c == '\t' || c == '\n' || c == ';') {
			if (count)
				break;
		} else if ((c != '"') && (count<buffsize-1)) {
			*cp++ = c;
			count++;
		}
	}
	*cp = 0;
#if DEBUG
	printf("|TOEN: %s, %d\n", token, count);
#endif
	return count ? 1 : 0;
}

/*
 * There doesn't seem to be a universally available library function
 * which converts broken-down _GMT_ time to seconds-in-epoch.
 * The following was borrowed from ISC dhcpd sources, where
 * it is noted that it might not be entirely accurate for odd seconds.
 * Since we're trying to get the same answer as dhcpd, that's just
 * fine here.
 */
static time_t
convert_time(struct tm lease_time) {
	static const int months [11] = { 31, 59, 90, 120, 151, 181,
						212, 243, 273, 304, 334 };
	time_t time = ((((((365 * (lease_time.tm_year - 1970) + /* Days in years since '70 */
			    (lease_time.tm_year - 1969) / 4 +   /* Leap days since '70 */
			    (lease_time.tm_mon > 1		/* Days in months this year */
				? months [lease_time.tm_mon - 2]
				: 0) +
			    (lease_time.tm_mon > 2 &&		/* Leap day this year */
			    !((lease_time.tm_year - 1972) & 3)) +
			    lease_time.tm_mday - 1) * 24) +	/* Day of month */
			    lease_time.tm_hour) * 60) +
			    lease_time.tm_min) * 60) + lease_time.tm_sec;

	return (time);
}

static int
load_dhcp(time_t now) {
	char namebuff[256];
	char *hostname = namebuff, *suffix = NULL;
	char token[MAXTOK], *dot;
	struct in_addr host_address;
	time_t ttd, tts;
	struct isc_lease *lease, *tmp;

	rewind(fp);
	LIST_INIT(&leases);

	while ((next_token(token, MAXTOK, fp))) {
		if (strcmp(token, "lease") == 0) {
			*hostname = 0;
			ttd = tts = (time_t)(-1);
			if (next_token(token, MAXTOK, fp) && 
			    (inet_pton(AF_INET, token, &host_address))) {
				if (next_token(token, MAXTOK, fp) && *token == '{') {
					while (next_token(token, MAXTOK, fp) && *token != '}') {
#if DEBUG
						printf("token: %s\n", token);
#endif
						if ((strcmp(token, "client-hostname") == 0) ||
						    (strcmp(token, "hostname") == 0)) {
							if (next_token(hostname, MAXDNAME, fp)) {
								if (*hostname == '}') {
									*hostname = 0;
								} else if (!canonicalise(hostname)) {
									if (foreground)
										printf("bad name(%s) in %s\n", hostname, leasefile);
									else
										syslog(LOG_ERR, "bad name in %s", leasefile); 
									*hostname = 0;
								}
							}
						} else if ((strcmp(token, "ends") == 0) ||
							    (strcmp(token, "starts") == 0)) {
								struct tm lease_time;
								int is_ends = (strcmp(token, "ends") == 0);
								if (next_token(token, MAXTOK, fp) &&  /* skip weekday */
								    next_token(token, MAXTOK, fp) &&  /* Get date from lease file */
								    sscanf (token, "%d/%d/%d", 
									&lease_time.tm_year,
									&lease_time.tm_mon,
									&lease_time.tm_mday) == 3 &&
								    next_token(token, MAXTOK, fp) &&
								    sscanf (token, "%d:%d:%d:", 
									&lease_time.tm_hour,
									&lease_time.tm_min, 
									&lease_time.tm_sec) == 3) {
									if (is_ends)
										ttd = convert_time(lease_time);
									else
										tts = convert_time(lease_time);
								}
						}
					}
				}

				/* missing info? */
				if (!*hostname)
					continue;
				if (ttd == (time_t)(-1))
					ttd = (time_t)0;

				/* We use 0 as infinite in ttd */
				if ((tts != -1) && (ttd == tts - 1))
					ttd = (time_t)0;

				if ((dot = strchr(hostname, '.'))) {
					if (!domain_suffix || hostname_isequal(dot+1, domain_suffix)) {
						if (foreground)
							printf("Other suffix in DHCP lease for %s", hostname);
						else
							syslog(LOG_WARNING, "Other suffix in DHCP lease for %s", hostname);

						suffix = (dot + 1);
						*dot = 0;
					} else
						suffix = domain_suffix;
				} else
					suffix = domain_suffix;

				LIST_FOREACH(lease, &leases, next) {
					if (hostname_isequal(lease->name, hostname)) {
						lease->expires = ttd;
						lease->addr = host_address;
						break;
					}
				}

				if (!lease) {
					if ((lease = malloc(sizeof(struct isc_lease))) == NULL)
						continue;
					lease->expires = ttd;
					lease->addr = host_address;
					lease->fqdn = NULL;
					lease->name = NULL;
					LIST_INSERT_HEAD(&leases, lease, next); 
				} else if (lease->fqdn != NULL)
						free(lease->fqdn);

				if (foreground)
					printf("Found hostname: %s.%s\n", hostname, suffix);

				if (asprintf(&lease->name, "%s", hostname) < 0) {
					LIST_REMOVE(lease, next);
					if (lease->name != NULL)
						free(lease->name);
					if (lease->fqdn != NULL)
						free(lease->fqdn);
					free(lease);
				}
				if (asprintf(&lease->fqdn, "%s.%s", hostname, suffix) < 0) {
					LIST_REMOVE(lease, next);
					if (lease->name != NULL)
						free(lease->name);
					if (lease->fqdn != NULL)
						free(lease->fqdn);
					free(lease);
				}
			}
		}
	}
 
	/* prune expired leases */
	LIST_FOREACH_SAFE(lease, &leases, next, tmp) {
		if (lease->expires != (time_t)0 && difftime(now, lease->expires) > 0) {
			if (lease->name)
				free(lease->name);
			if (lease->fqdn)
				free(lease->fqdn);
			LIST_REMOVE(lease, next);
			free(lease);
		}
	}

	return (0);
}

static int
write_status() {
	struct isc_lease *lease;
	struct stat tmp;
	size_t tmpsize;
	int fd;
	
	fd = open(HOSTS, O_RDWR | O_CREAT | O_FSYNC);
        if (fd < 0)
		return 1;
	if (fstat(fd, &tmp) < 0)
		tmpsize = hostssize;
	else
		tmpsize = tmp.st_size;
	if (tmpsize < hostssize) {
		if (foreground)
			printf("%s changed size from original!", HOSTS);
		else
			syslog(LOG_WARNING, "%s changed size from original!", HOSTS);
		hostssize = tmpsize;
	}
	ftruncate(fd, hostssize);
	if (lseek(fd, 0, SEEK_END) < 0) {
		close(fd);
		return 2;
	}
	/* write the tmp hosts file */
	dprintf(fd, "\n# dhcpleases automatically entered\n"); /* put a blank line just to be on safe side */
	LIST_FOREACH(lease, &leases, next) {
		if (foreground)
			printf("%s\t%s %s\t\t# dynamic entry from dhcpd.leases\n", inet_ntoa(lease->addr),
				lease->fqdn ? lease->fqdn  : "empty", lease->name ? lease->name : "empty");
		else
			dprintf(fd, "%s\t%s %s\t\t# dynamic entry from dhcpd.leases\n", inet_ntoa(lease->addr),
				lease->fqdn ? lease->fqdn  : "empty", lease->name ? lease->name : "empty");
	}
	close(fd);

	return (0);
}

static void
cleanup() {
	struct isc_lease *lease, *tmp;

	LIST_FOREACH_SAFE(lease, &leases, next, tmp) {
		if (lease->fqdn)
			free(lease->fqdn);
		if (lease->name)
			free(lease->name);
		LIST_REMOVE(lease, next);
		free(lease);
	}

	return;
}

static void
signal_process() {
	FILE *fd;
	int size = 0;
	char *pid = NULL, *pc;
	int c, pidno;

	if (pidfile == NULL)
		goto error;
	size = fsize(pidfile);
	if (size < 0)
		goto error;

	fd = fopen(pidfile, "r");
	if (fd == NULL)
		goto error;

	pid = calloc(size, size);
	if (pid == NULL) {
		fclose(fd);
		goto error;
	}
	pc = pid;
	while ((c = getc(fd)) != EOF) {
		if (c == '\n')
			break;
		*pc++ = c;
	}
	fclose(fd);

	pidno = atoi(pid);
	free(pid);

	syslog(LOG_INFO, "Sending HUP signal to dns daemon(%u)", pidno);
	if (kill((pid_t)pidno, SIGHUP) < 0)
		goto error;

	return;
error:
	syslog(LOG_ERR, "Could not deliver signal HUP to process because its pidfile does not exist, %m.");
	return;
}

static void
handle_signal(int sig) {
	int size;

        switch(sig) {
        case SIGHUP:
		size = fsize(HOSTS);
		if (size < 0)
			syslog(LOG_ERR, "file `%s' size unknown", HOSTS);
		else
			hostssize = size;
                break;
        case SIGTERM:
		unlink(PIDFILE);
		cleanup();
                exit(0);
                break;
        default:
                syslog(LOG_WARNING, "unhandled signal");
        }
}

int
main(int argc, char **argv) {
	struct kevent evlist;    /* events we want to monitor */
	struct kevent chlist;    /* events that were triggered */
	struct sigaction sa;
	time_t	now;
	int kq, nev, leasefd = 0, pidf, ch;

	if (argc != 5) {
	}

	while ((ch = getopt(argc, argv, "c:d:fp:h:l:")) != -1) {
		switch (ch) {
		case 'c':
			command = optarg;
			break;
		case 'd':
			domain_suffix = optarg;
			break;
		case 'f':
			foreground = 1;
			break;
		case 'p':
			pidfile = optarg;
			break;
		case 'h':
			HOSTS = optarg;
			break;
		case 'l':
			leasefile = optarg;
			break;
		default:
			perror("Wrong number of arguments given."); /* XXX: usage */
			exit(2);
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (leasefile == NULL) {
		syslog(LOG_ERR, "lease file is mandatory as parameter");	
		perror("lease file is mandatory as parameter");	
		exit(1);
	}
	if (!fexist(leasefile)) {
		syslog(LOG_ERR, "lease file needs to exist before starting dhcpleases");	
		perror("lease file needs to exist before starting dhcpleases");	
		exit(1);
	}
	if (domain_suffix == NULL) {
		syslog(LOG_ERR, "a domain suffix is not passed as argument using 'local' as suffix");
		domain_suffix = "local";
	}

	if (pidfile == NULL && !foreground) {
		syslog(LOG_ERR, "pidfile argument not passed it is mandatory");
		perror("pidfile argument not passed it is mandatory");
		exit(1);
	}

	if (!foreground) {
		int size;

		if (HOSTS == NULL) {
			syslog(LOG_ERR, "You need to specify the hosts file path.");
			perror("You need to specify the hosts file path.");
			exit(8);
		}
		if (!fexist(HOSTS)) {
			syslog(LOG_ERR, "Hosts file %s does not exist!", HOSTS);
			perror("Hosts file passed as parameter does not exist");
			exit(8);
		}

		hostssize = size = fsize(HOSTS);
		if (size < 0) {
			syslog(LOG_ERR, "Error while getting %s file size.", HOSTS);
			perror("Error while getting /etc/hosts file size.");
			exit(6);
		}

		closefrom(3);

		if (daemon(0, 0) < 0) {
			syslog(LOG_ERR, "Could not daemonize");
			perror("Could not daemonize");
			exit(4);
		}
	}

reopen:
	leasefd = open(leasefile, O_RDONLY);
	if (leasefd < 0) {
		syslog(LOG_ERR, "Could not get descriptor");
		perror("Could not get descriptor");
		exit(6);
	}

	fp = fdopen(leasefd, "r");
	if (fp == NULL) {
		syslog(LOG_ERR, "could not open leases file");
		perror("could not open leases file");
		exit(5);
	}

	if (!foreground) {
		pidf = open(PIDFILE, O_RDWR | O_CREAT | O_FSYNC);
		if (pidf < 0)
			syslog(LOG_ERR, "could not write pid file, %m");
		else {
			ftruncate(pidf, 0);
			dprintf(pidf, "%u\n", getpid());
			close(pidf);
		}

		/*
		 * Catch SIGHUP in order to reread configuration file.
		 */
		sa.sa_handler = handle_signal;
		sa.sa_flags = SA_SIGINFO|SA_RESTART;
		sigemptyset(&sa.sa_mask);
		if (sigaction(SIGHUP, &sa, NULL) < 0) {
			syslog(LOG_ERR, "unable to set signal handler, %m");
			exit(9);
		}
		if (sigaction(SIGTERM, &sa, NULL) < 0) {
			syslog(LOG_ERR, "unable to set signal handler, %m");
			exit(10);
		}

		/* Create a new kernel event queue */
		if ((kq = kqueue()) == -1)
			exit(1);
	}

	now = time(NULL);
	if (command == NULL) {
		load_dhcp(now);

		write_status();
		//syslog(LOG_INFO, "written temp hosts file after modification event.");

		cleanup();
		//syslog(LOG_INFO, "Cleaned up.");

		if (!foreground)
			signal_process();
	}

	if (!foreground) {
		/* Initialise kevent structure */
		EV_SET(&chlist, leasefd, EVFILT_VNODE, EV_ADD | EV_CLEAR | EV_ENABLE | EV_ONESHOT,
			NOTE_WRITE | NOTE_ATTRIB | NOTE_DELETE | NOTE_RENAME | NOTE_LINK, 0, NULL);
		/* Loop forever */
		for (;;) {
			nev = kevent(kq, &chlist, 1, &evlist, 1, NULL);
			if (nev == -1) {
				syslog(LOG_ERR, "kqueue error: unkown");
				close(leasefd);
				goto reopen;
			} else if (nev > 0) {
				if (evlist.flags & EV_ERROR) {
					syslog(LOG_ERR, "EV_ERROR: %s\n", strerror(evlist.data));
					close(leasefd);
					goto reopen;
				}
				if (evlist.fflags & (NOTE_DELETE | NOTE_RENAME | NOTE_LINK)) {
					close(leasefd);
					goto reopen;
				}
				now = time(NULL);
				if (command != NULL)
					system(command);
				else {
					load_dhcp(now);

					write_status();
					//syslog(LOG_INFO, "written temp hosts file after modification event.");

					cleanup();
					//syslog(LOG_INFO, "Cleaned up.");

					signal_process();
				}
			}
		}
	}

	fclose(fp);
	unlink(PIDFILE);
	return (0);
}
