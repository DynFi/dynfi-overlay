# $FreeBSD$

PORTNAME=	opnsense-core
PORTVERSION=	21.10.1
PORTREVISION=	37
CATEGORIES=	dynfi
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}
DISTFILES=

MAINTAINER=	manu@FreeBSD.org
COMMENT=	OPNsense Core package

LICENSE=	BSD2CLAUSE

IGNORE_WITH_PHP=	80

OPNSENSE_PORT_REV=	${PORTREVISION}

RUN_DEPENDS=	ca_root_nss>=0:security/ca_root_nss \
		choparp>=0:net-mgmt/choparp \
		cpustats>=0:dynfi/cpustats \
		dhcp6c>=0:dynfi/dhcp6c \
		dhcpleases>=0:dynfi/dhcpleases \
		dnsmasq>=0:dns/dnsmasq \
		dpinger>=0:net/dpinger \
		expiretable>=0:security/expiretable \
		filterlog>=0:dynfi/filterlog \
		ifinfo>=0:dynfi/ifinfo \
		flock>=0:sysutils/flock \
		flowd>=0:net-mgmt/flowd \
		hostapd>=0:net/hostapd \
		isc-dhcp44-relay>=0:net/isc-dhcp44-relay \
		isc-dhcp44-server>=0:net/isc-dhcp44-server \
		lighttpd>=0:www/lighttpd \
		monit>=0:sysutils/monit \
		mpd5>=0:net/mpd5 \
		ntp>=0:net/ntp \
		openssh-portable>=0:security/openssh-portable \
		ldns>=0:dns/ldns \
		openvpn>=0:security/openvpn \
		opnsense-update>=0:dynfi/opnsense-update \
		pam_opnsense>=0:dynfi/pam_opnsense \
		pftop>=0:sysutils/pftop \
		iftop>=0:net-mgmt/iftop \
		radvd>=0:dynfi/radvd \
		rate>=0:net-mgmt/rate \
		rrdtool>=0:databases/rrdtool \
		samplicator>=0:net/samplicator \
		smartmontools>=0:sysutils/smartmontools \
		squid>=0:www/squid \
		strongswan>=0:security/strongswan \
		sudo>=0:security/sudo \
		suricata>=0:security/suricata \
		syslog-ng>=0:sysutils/syslog-ng \
		unbound>=0:dns/unbound \
		wpa_supplicant>=0:security/wpa_supplicant \
		zip>=0:archivers/zip \
		${PYTHON_PKGNAMEPREFIX}Jinja2>=0:devel/py-Jinja2@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}dnspython>=0:dns/py-dnspython@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}netaddr>=0:net/py-netaddr@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}requests>=0:www/py-requests@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}sqlite3>=0:databases/py-sqlite3@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}ujson>=0:devel/py-ujson@${PY_FLAVOR} \
		${PHP_PKGNAMEPREFIX}phalcon4>=0:www/phalcon4 \
		${PHP_PKGNAMEPREFIX}pecl-radius>=0:net/pecl-radius \
		${PHP_PKGNAMEPREFIX}ctype>=0:textproc/${PHP_PKGNAMEPREFIX}ctype \
		${PHP_PKGNAMEPREFIX}dom>=0:textproc/${PHP_PKGNAMEPREFIX}dom \
		${PHP_PKGNAMEPREFIX}filter>=0:security/${PHP_PKGNAMEPREFIX}filter \
		${PHP_PKGNAMEPREFIX}gettext>=0:devel/${PHP_PKGNAMEPREFIX}gettext \
		${PHP_PKGNAMEPREFIX}json>=0:devel/${PHP_PKGNAMEPREFIX}json \
		${PHP_PKGNAMEPREFIX}ldap>=0:net/${PHP_PKGNAMEPREFIX}ldap \
		${PHP_PKGNAMEPREFIX}pecl-mcrypt>=0:security/pecl-mcrypt \
		${PHP_PKGNAMEPREFIX}openssl>=0:security/${PHP_PKGNAMEPREFIX}openssl \
		${PHP_PKGNAMEPREFIX}pdo>=0:databases/${PHP_PKGNAMEPREFIX}pdo \
		${PHP_PKGNAMEPREFIX}session>=0:www/${PHP_PKGNAMEPREFIX}session \
		${PHP_PKGNAMEPREFIX}simplexml>=0:textproc/${PHP_PKGNAMEPREFIX}simplexml \
		${PHP_PKGNAMEPREFIX}sockets>=0:net/${PHP_PKGNAMEPREFIX}sockets \
		${PHP_PKGNAMEPREFIX}sqlite3>=0:databases/${PHP_PKGNAMEPREFIX}sqlite3 \
		${PHP_PKGNAMEPREFIX}xml>=0:textproc/${PHP_PKGNAMEPREFIX}xml \
		${PHP_PKGNAMEPREFIX}phpseclib>=0:dynfi/phpseclib \
		openssl>=0:security/openssl \
		redis>=0:databases/redis \
		zerotier>=0:net/zerotier \
		clamav>=0:security/clamav \
		c-icap>=0:www/c-icap \
		c-icap-modules>=0:www/c-icap-modules


USES=	python:3.9 php:flavors shebangfix
USE_PHP=	curl zlib sockets

SHEBANG_FILES=	src/opnsense/scripts/systemhealth/fetchData.py \
		src/opnsense/scripts/systemhealth/activity.py \
		src/opnsense/scripts/systemhealth/flush_rrd.py \
		src/opnsense/scripts/systemhealth/listReports.py

MAKE_ENV+=	VERSION=${PORTVERSION}

do-extract:
	${MKDIR} ${WRKSRC}
.if defined(OPNSENSE_PORT_REV)
	tar xzf ${FILESDIR}/${PORTNAME}-${PORTVERSION}-${OPNSENSE_PORT_REV}.tgz -C ${WRKSRC}
.else
	tar xzf ${FILESDIR}/${PORTNAME}-${PORTVERSION}.tgz -C ${WRKSRC}
.endif

do-build:
	(cd ${WRKSRC} && make install DESTDIR=${STAGEDIR} FLAVOUR=OpenSSL VERSION=${PORTVERSION})

post-install:
	${CP} ${STAGEDIR}/${LOCALBASE}/etc/config.xml.sample ${STAGEDIR}/${LOCALBASE}/etc/config.xml
	${CP} ${STAGEDIR}/${LOCALBASE}/etc/bogons.sample ${STAGEDIR}/${LOCALBASE}/etc/bogons
	${CP} ${STAGEDIR}/${LOCALBASE}/etc/bogonsv6.sample ${STAGEDIR}/${LOCALBASE}/etc/bogonsv6
	${CP} ${STAGEDIR}/${LOCALBASE}/opnsense/service/templates/OPNsense/IDS/custom.yaml.sample ${STAGEDIR}/${LOCALBASE}/opnsense/service/templates/OPNsense/IDS/custom.yaml

.include <bsd.port.mk>
