PORTNAME=	DynFi
DISTVERSION=	1
PORTREVISION=	2
CATEGORIES=	dynfi
DISTFILES=

MAINTAINER=	oshogbo@DynFi.com
COMMENT=	Package agregating all the packages required to run DynFi Firewall

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	aquantia-atlantic-kmod>=0:net/aquantia-atlantic-kmod \
		iperf3>=0:benchmarks/iperf3 \
		bind916>=0:dns/bind916 \
		ddns>=0:dns/ddns \
		qemu-guest-agent>=0:emulators/qemu@guestagent \
		virtualbox-ose-additions-nox11>=0:emulators/virtualbox-ose-additions-nox11 \
		open-vm-tools-nox11>=0:emulators/open-vm-tools@nox11 \
		rspamd>=0:mail/rspamd \
		net-snmp>=0:net-mgmt/net-snmp \
		nrpe3>=0:net-mgmt/nrpe3 \
		zabbix5-agent>=0:net-mgmt/zabbix5-agent \
		freeradius3>=0:net/freeradius3 \
		frr7>=0:net/frr7 \
		haproxy>=0:net/haproxy \
		siproxd>=0:net/siproxd \
		lcdproc>=0:sysutils/lcdproc \
		autossh>=0:security/autossh \
		beep>=0:audio/beep \
		intel-ix-kmod>=0:net/intel-ix-kmod \
		dynfi-rpz>=0:dynfi/dynfi-rpz \
		dynfi-confs>=0:dynfi/dynfi-confs \
		n2disk>=0:dynfi/n2disk \
		nprobe>=0:dynfi/nprobe \
		ntopng>=0:dynfi/ntopng \
		freeradius3>0:net/freeradius3 \
		outline-ss-server>0:dynfi/outline-ss-server \
		ddclient>=0:dns/ddclient \
		wireguard-tools>=0:net/wireguard-tools \
		${PHP_PKGNAMEPREFIX}opnsense-core>=0:dynfi/opnsense-core

USES=   php:flavors

do-extract:
	${MKDIR} ${WRKSRC}
	touch ${WRKSRC}/Makefile

do-build:
	cd ${WRKSRC}

do-install:

post-install:
	touch ${STAGEDIR}/.dynfi

.include <bsd.port.mk>
