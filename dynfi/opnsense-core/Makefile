# $FreeBSD$

PORTNAME=	opnsense-core
PORTVERSION=	24.1.3
PORTREVISION=	18
CATEGORIES=	dynfi
PKGNAMEPREFIX=	${PHP_PKGNAMEPREFIX}
DISTFILES=

MAINTAINER=	manu@FreeBSD.org
COMMENT=	OPNsense Core package

LICENSE=	BSD2CLAUSE

OPNSENSE_PORT_REV=	${PORTREVISION}

RUN_DEPENDS=	ca_root_nss>=0:security/ca_root_nss \
		choparp>=0:net-mgmt/choparp \
		cpdup>=0:sysutils/cpdup \
		cyrus-sasl>=0:security/cyrus-sasl2 \
		cyrus-sasl-gssapi>=0:security/cyrus-sasl2-gssapi \
		cpustats>=0:dynfi/cpustats \
		dhcp6c>=0:dynfi/dhcp6c \
		dnsmasq>=0:dns/dnsmasq \
		dpinger>=0:net/dpinger \
		expiretable>=0:security/expiretable \
		opie>=0:security/opie \
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
		unbound>=0:dns/unbound \
		wpa_supplicant>=0:security/wpa_supplicant \
		zip>=0:archivers/zip \
		kea>0:net/kea \
		${PYTHON_PKGNAMEPREFIX}Jinja2>=0:devel/py-Jinja2@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}aioquic>=0:www/py-aioquic@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}anyio>=0:devel/py-anyio@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}async_generator>=0:devel/py-async_generator@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}attrs>=0:devel/py-attrs@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}Babel>=0:devel/py-babel@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}bottleneck>=0:math/py-bottleneck@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}certifi>=0:security/py-certifi@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}cffi>=0:devel/py-cffi@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}charset-normalizer>=0:textproc/py-charset-normalizer@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}cryptography>=0:security/py-cryptography@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}python-dateutil>=0:devel/py-python-dateutil@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}dnspython>=0:dns/py-dnspython@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}duckdb>=0:databases/py-duckdb@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}exceptiongroup>=0:devel/py-exceptiongroup@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}h11>=0:net/py-h11@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}h2>=0:www/py-h2@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}hpack>=0:www/py-hpack@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}httpcore>=0:www/py-httpcore@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}httpx>=0:www/py-httpx@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}hyperframe>=0:www/py-hyperframe@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}idna>=0:dns/py-idna@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}markupsafe>=0:textproc/py-markupsafe@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}netaddr>=0:net/py-netaddr@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numexpr>=0:math/py-numexpr@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy>=0:math/py-numpy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}openssl>=0:security/py-openssl@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}outcome>=0:devel/py-outcome@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pandas>=0:math/py-pandas@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyasn1-modules>=0:devel/py-pyasn1-modules@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyasn1>=0:devel/py-pyasn1@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pycparser>=0:devel/py-pycparser@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pylsqpack>=0:www/py-pylsqpack@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pysocks>=0:net/py-pysocks@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pytz>=0:devel/py-pytz@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}requests>=0:www/py-requests@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}service-identity>=0:security/py-service-identity@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}setuptools>=0:devel/py-setuptools@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}six>=0:devel/py-six@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}sniffio>=0:devel/py-sniffio@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}sortedcontainers>=0:devel/py-sortedcontainers@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}sqlite3>=0:databases/py-sqlite3@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}trio>=0:net/py-trio@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}typing-extensions>=0:devel/py-typing-extensions@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}tzdata>=0:devel/py-tzdata@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}ujson>=0:devel/py-ujson@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}urllib3>=0:net/py-urllib3@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}vici>=0:security/py-vici@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyyaml>=0:devel/py-pyyaml@${PY_FLAVOR} \
		${PHP_PKGNAMEPREFIX}ctype>=0:textproc/${PHP_PKGNAMEPREFIX}ctype \
		${PHP_PKGNAMEPREFIX}dom>=0:textproc/${PHP_PKGNAMEPREFIX}dom \
		${PHP_PKGNAMEPREFIX}filter>=0:security/${PHP_PKGNAMEPREFIX}filter \
		${PHP_PKGNAMEPREFIX}gettext>=0:devel/${PHP_PKGNAMEPREFIX}gettext \
		${PHP_PKGNAMEPREFIX}google-api-php-client>=0:dynfi/google-api-php-client \
		${PHP_PKGNAMEPREFIX}ldap>=0:net/${PHP_PKGNAMEPREFIX}ldap \
		${PHP_PKGNAMEPREFIX}mbstring>=0:converters/${PHP_PKGNAMEPREFIX}mbstring \
		${PHP_PKGNAMEPREFIX}pcntl>=0:devel/${PHP_PKGNAMEPREFIX}pcntl \
		${PHP_PKGNAMEPREFIX}pdo>=0:databases/${PHP_PKGNAMEPREFIX}pdo \
		${PHP_PKGNAMEPREFIX}pecl-mcrypt>=0:security/pecl-mcrypt \
		${PHP_PKGNAMEPREFIX}pecl-radius>=0:net/pecl-radius \
		${PHP_PKGNAMEPREFIX}phalcon>=0:www/phalcon \
		${PHP_PKGNAMEPREFIX}phpseclib>=0:dynfi/phpseclib \
		${PHP_PKGNAMEPREFIX}session>=0:www/${PHP_PKGNAMEPREFIX}session \
		${PHP_PKGNAMEPREFIX}simplexml>=0:textproc/${PHP_PKGNAMEPREFIX}simplexml \
		${PHP_PKGNAMEPREFIX}sockets>=0:net/${PHP_PKGNAMEPREFIX}sockets \
		${PHP_PKGNAMEPREFIX}sqlite3>=0:databases/${PHP_PKGNAMEPREFIX}sqlite3 \
		${PHP_PKGNAMEPREFIX}xml>=0:textproc/${PHP_PKGNAMEPREFIX}xml \
		${PHP_PKGNAMEPREFIX}zlib>=0:archivers/${PHP_PKGNAMEPREFIX}zlib \
		openssl>=0:security/openssl \
		redis>=0:databases/redis \
		zerotier>=0:net/zerotier \
		syslog-ng>=0:sysutils/syslog-ng \
		clamav>=0:security/clamav \
		c-icap>=0:www/c-icap \
		c-icap-modules>=0:www/c-icap-modules


USES=	python:3.11 php:flavors shebangfix
USE_PHP=	curl zlib sockets

SHEBANG_FILES=	src/opnsense/scripts/health/fetchData.py \
		src/opnsense/scripts/health/flush_rrd.py \
		src/opnsense/scripts/health/listReports.py \
		src/opnsense/scripts/system/activity.py

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
