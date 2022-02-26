# $FreeBSD$

PORTNAME=	ntopng
PORTREVISION=	1
CATEGORIES=	dynfi
DISTFILES=
PLIST=           ${.CURDIR}/pkg-plist

PORTVERSION=	5.3.220226
RUN_DEPENDS= 	bash>0:shells/bash \
		libmaxminddb>0:net/libmaxminddb \
		libsodium>0:security/libsodium \
		libzmq4>0:net/libzmq4 \
		lua53>0:lang/lua53 \
		redis>0:databases/redis \
		rrdtool>0:databases/rrdtool \
		sqlite3>0:databases/sqlite3 \
		zstd>0:archivers/zstd

COMMENT=High speed network traffic monitor

MAINTAINER=	info@dynfi.com

LICENSE=	BSD2CLAUSE

MAKE_ENV+=	VERSION=${PORTVERSION}

NO_BUILD=

do-extract:
	${MKDIR} ${WRKSRC}
	tar xzf ${FILESDIR}/${PORTNAME}-${PORTVERSION}.tgz -C ${WRKSRC} --exclude '+*MANIFEST*'

do-install:
	cp -Rvp ${WRKSRC}/ ${STAGEDIR}
	echo "ASDASD"
	ls /wrkdirs/overlays/dynfi-overlay/dynfi/ntopng/work/stage/usr/local/share/man/man8/ntopng.8

.include <bsd.port.mk>
