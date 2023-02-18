# $FreeBSD$

PORTNAME=	n2disk	
PORTREVISION=	1
CATEGORIES=	dynfi
DISTFILES=
PLIST=           ${.CURDIR}/pkg-plist

PORTVERSION=3.7.230218
RUN_DEPENDS= libzmq4>0:net/libzmq4

COMMENT=Network traffic recorder

MAINTAINER=	info@dynfi.com

LICENSE=	BSD2CLAUSE

MAKE_ENV+=	VERSION=${PORTVERSION}

NO_BUILD=

do-extract:
	${MKDIR} ${WRKSRC}
	tar xzf ${FILESDIR}/${PORTNAME}-${PORTVERSION}.tgz -C ${WRKSRC} --exclude '+*MANIFEST*'

do-install:
	cp -Rvp ${WRKSRC}/ ${STAGEDIR}

.include <bsd.port.mk>
