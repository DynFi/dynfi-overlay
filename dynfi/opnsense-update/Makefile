# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	opnsense-update
PORTVERSION=	21.1.5
PORTREVISION=	16
CATEGORIES=	dynfi
MASTER_SITES=	#empty
DISTFILES=	#none
EXTRACT_ONLY=	#empty

MAINTAINER=	franco@opnsense.org
COMMENT=	OPNsense update utilities

LICENSE=	BSD2CLAUSE

LIB_DEPENDS+=	libucl.so:textproc/libucl

USES=		ssl uidfix

USE_HARDENING=	safestack

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>
