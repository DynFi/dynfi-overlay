# Created by: Ad Schellevis <ad@opnsense.org>
# $FreeBSD$

PORTNAME=	pam_opnsense

PORTVERSION=	24.1
CATEGORIES=	sysutils
PKGNAMESUFFIX=

MAINTAINER=	ad@opnsense.org
COMMENT=	OPNsense shared authentication system using PAM

LICENSE=	BSD2CLAUSE

USES=  fakeroot
USE_GITHUB=	yes
GH_ACCOUNT=	opnsense

post-stage:
	${RM} ${STAGEDIR}${PREFIX}/lib/*.a

.include <bsd.port.mk>
