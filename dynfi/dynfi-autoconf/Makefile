# $FreeBSD$

PORTNAME=  	dynfi-autoconf
PORTVERSION=	1
PORTREVISION=	1
CATEGORIES=	dynfi
DISTFILES=

MAINTAINER=	oshogbo@DynFi.com
COMMENT=	DynFI autoconf 

LICENSE=	BSD2CLAUSE

do-extract:

do-build:

do-install:
	mkdir -p ${STAGEDIR}${PREFIX}/etc
	cp -Rvp ${FILESDIR}/etc/* ${STAGEDIR}${PREFIX}/etc
	chmod +x ${STAGEDIR}${PREFIX}/etc/rc.syshook.d/start/*
	chmod +x ${STAGEDIR}${PREFIX}/etc/rc.syshook.d/stop/*
	chmod +x ${STAGEDIR}${PREFIX}/etc/rc.d/*

post-install:

.include <bsd.port.mk>
