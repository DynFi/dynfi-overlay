PROG=	opnsense-verify
MAN=	opnsense-verify.8

SRCS=	config.c pkg.c

CFLAGS+=-I/usr/local/include
LDADD+=	-lsbuf -lssl -lcrypto
LDADD+=	-L/usr/local/lib -lucl

LOCALBASE?=${DESTDIR}/usr/local
PREFIX?=${LOCALBASE}

BINDIR=	${PREFIX}/sbin
MANDIR=	${PREFIX}/share/man/man

.include <bsd.prog.mk>
