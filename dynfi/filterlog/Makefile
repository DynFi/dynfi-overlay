# Created by: Franco Fichtner <franco@opnsense.org>
# $FreeBSD$

PORTNAME=	filterlog
PORTVERSION=	0.6
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# none
EXTRACT_ONLY=	# empty

MAINTAINER=	franco@opnsense.org
COMMENT=	Parse pflog(4) output

LICENSE=	BSD3CLAUSE

USES=uidfix
USE_HARDENING=	safestack

do-extract:
	${CP} -r ${FILESDIR} ${WRKSRC}

.include <bsd.port.mk>
