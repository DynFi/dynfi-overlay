# Treat this directory as a pluggable ports category:
THIS_CATEGORY=	dynfi
VALID_CATEGORIES=${THIS_CATEGORY}
CATEGORIES:=	${THIS_CATEGORY} ${CATEGORIES}
PKGORIGIN=	${.CURDIR:S/${PORTSDIR}\///1}
