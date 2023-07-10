# $FreeBSD$

PORTNAME=  	dynfi-lcdd
PORTVERSION=	1
PORTREVISION=	1
CATEGORIES=	dynfi
DISTFILES=

MAINTAINER=	oshogbo@DynFi.com
COMMENT=	DynFI rpz block list

LICENSE=	BSD2CLAUSE

do-extract:

do-build:

do-install:
	mkdir -p ${STAGEDIR}${PREFIX}/bin
	mkdir -p ${STAGEDIR}${PREFIX}/etc
	cp -Rvp ${FILESDIR}/script/* ${STAGEDIR}${PREFIX}/bin
	cp -Rvp ${FILESDIR}/etc/* ${STAGEDIR}${PREFIX}/etc
	chmod +x ${STAGEDIR}${PREFIX}/etc/rc.syshook.d/start/*
	chmod +x ${STAGEDIR}${PREFIX}/etc/rc.syshook.d/stop/*
	chmod +x ${STAGEDIR}${PREFIX}/etc/rc.d/*

post-install:

.include <bsd.port.mk>
