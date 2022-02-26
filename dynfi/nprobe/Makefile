# $FreeBSD$

PORTNAME=	nprobe
PORTREVISION=	1
CATEGORIES=	dynfi
DISTFILES=
PLIST=           ${.CURDIR}/pkg-plist


PORTVERSION= 9.7.220226
RUN_DEPENDS= json-c>0:devel/json-c \
	     libmaxminddb>0:net/libmaxminddb \
	     librdkafka>0:net/librdkafka \
	     libzmq4>0:net/libzmq4 \
	     libgcrypt>0:security/libgcrypt \
	     libgpg-error>0:security/libgpg-error \
	     libpcap>0:net/libpcap

# libcrypt, libgpg, libcap are not listed by ntop. Please do not remove!

MAINTAINER=	info@dynfi.com
COMMENT=	NetFlow/IPFIX probe and collector

LICENSE=	BSD2CLAUSE

MAKE_ENV+=	VERSION=${PORTVERSION}

NO_BUILD=

do-extract:
	${MKDIR} ${WRKSRC}
	tar xzf ${FILESDIR}/${PORTNAME}-${PORTVERSION}.tgz -C ${WRKSRC} --exclude '+*MANIFEST*'

do-install:
	cp -Rvp ${WRKSRC}/ ${STAGEDIR}

.include <bsd.port.mk>
