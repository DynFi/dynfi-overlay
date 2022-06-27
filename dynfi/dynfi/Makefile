PORTNAME=	DynFi
DISTVERSION=	1
PORTREVISION=	1
CATEGORIES=	dynfi
DISTFILES=

MAINTAINER=	oshogbo@DynFi.com
COMMENT=	Package agregating all the packages required to run DynFi Firewall

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	aquantia-atlantic-kmod>=0:net/aquantia-atlantic-kmod \
		autossh>=0:security/autossh \
		beep>=0:audio/beep \
		intel-ix-kmod>=0:net/intel-ix-kmod \
		dynfi-rpz>=0:dynfi/dynfi-rpz \
		n2disk>=0:dynfi/n2disk \
		nprobe>=0:dynfi/nprobe \
		ntopng>=0:dynfi/ntopng \
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
