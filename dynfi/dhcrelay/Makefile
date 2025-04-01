PORTNAME=	dhcrelay
DISTVERSION=	1.0
CATEGORIES=	dynfi

MAINTAINER=	franco@opnsense.org
COMMENT=	OpenBSD dhcrelay daemons
WWW=		https://github.com/opnsense/dhcrelay

LICENSE=	BSD3CLAUSE

CONFLICTS_INSTALL=	isc-dhcp44-relay

USE_GITHUB=	yes
GH_ACCOUNT=	opnsense

do-install:
	find ${WRKSRC}
	${INSTALL_PROGRAM} ${WRKSRC}/usr.sbin/dhcrelay/dhcrelay ${STAGEDIR}${PREFIX}/sbin
	${INSTALL_PROGRAM} ${WRKSRC}/usr.sbin/dhcrelay6/dhcrelay6 ${STAGEDIR}${PREFIX}/sbin

.include <bsd.port.mk>
