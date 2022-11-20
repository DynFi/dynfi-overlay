# $FreeBSD$

PORTNAME=  	dynfi-rpz
PORTVERSION=	1
PORTREVISION=	3
CATEGORIES=	dynfi
DISTFILES=

MAINTAINER=	oshogbo@DynFi.com
COMMENT=	DynFI rpz block list

LICENSE=	BSD2CLAUSE

do-extract:

do-build:

do-install:
	mkdir -p ${STAGEDIR}${PREFIX}/share/dynfi/rpz/
	cp -Rvp ${FILESDIR}/conf/* ${STAGEDIR}${PREFIX}/share/dynfi/rpz/

post-install:

.include <bsd.port.mk>
