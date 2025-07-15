PORTNAME=	DynFi
DISTVERSION=	2
PORTREVISION=	6
CATEGORIES=	dynfi
DISTFILES=

MAINTAINER=	oshogbo@DynFi.com
COMMENT=	Package agregating all the packages required to run DynFi Firewall

LICENSE=	AGPLv3

RUN_DEPENDS=	aquantia-atlantic-kmod>=0:net/aquantia-atlantic-kmod \
		iperf3>=0:benchmarks/iperf3 \
		bind918>=0:dns/bind918 \
		ddns>=0:dns/ddns \
		qemu-guest-agent>=0:emulators/qemu@guestagent \
		open-vm-tools-nox11>=0:emulators/open-vm-tools@nox11 \
		rspamd>=0:mail/rspamd \
		net-snmp>=0:net-mgmt/net-snmp \
		nrpe>=0:net-mgmt/nrpe \
		zabbix6-agent>=0:net-mgmt/zabbix6-agent \
		freeradius3>=0:net/freeradius3 \
		frr8>=0:net/frr8 \
		haproxy>=0:net/haproxy \
		siproxd>=0:net/siproxd \
		lcdproc>=0:sysutils/lcdproc \
		autossh>=0:security/autossh \
		beep>=0:audio/beep \
		intel-ix-kmod>=0:net/intel-ix-kmod \
		dynfi-autoconf>=0:dynfi/dynfi-autoconf \
		dynfi-confs>=0:dynfi/dynfi-confs \
		dynfi-lcdd>=0:dynfi/dynfi-lcdd \
		dynfi-rpz>=0:dynfi/dynfi-rpz \
		nprobe>=0:dynfi/nprobe \
		ntopng>=0:dynfi/ntopng \
		freeradius3>0:net/freeradius3 \
		outline-ss-server>0:dynfi/outline-ss-server \
		ddclient>=0:dns/ddclient \
		wireguard-tools>=0:net/wireguard-tools \
		crowdsec>0:security/crowdsec \
		crowdsec-firewall-bouncer>0:security/crowdsec-firewall-bouncer \
		${PYTHON_PKGNAMEPREFIX}cloud-init>0:net/cloud-init@${PY_FLAVOR} \
		${PHP_PKGNAMEPREFIX}opnsense-core>=0:dynfi/opnsense-core

#virtualbox-ose-additions-nox11>=0:emulators/virtualbox-ose-additions-nox11 \

USES=	python:3.11 php:flavors

do-extract:
	${MKDIR} ${WRKSRC}
	touch ${WRKSRC}/Makefile

do-build:
	cd ${WRKSRC}

do-install:

post-install:
	touch ${STAGEDIR}/.dynfi

.include <bsd.port.mk>
