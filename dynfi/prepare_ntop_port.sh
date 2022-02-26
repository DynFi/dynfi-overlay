#!/bin/sh

ABI="FreeBSD:13:amd64"

case "${1}" in
  nprobe)
	;;
  ntopng)
    	;;
  n2disk)
    	;;
  *)
	echo "Wrong usage"
	exit 1
	;;
esac

pkg="${1}"
cd "${pkg}" || exit 1

pkg_cmd() {
	pkg -C ntop.conf -oABI="${ABI}" -R ".." $*
}

pkg_cmd fetch -o "./files" -y "${pkg}" 

PKG_INFO=`pkg_cmd search --raw --raw-format json -x "^${pkg}-.*$"`
PKG_NAME=`echo ${PKG_INFO} | jq -r '.path'`
NEW_PKG_NAME=`echo "${PKG_NAME}" | sed 's/.pkg/.tgz/'`

mv "files/${PKG_NAME}" "files/${NEW_PKG_NAME}"

PKG_VERSION=`echo ${PKG_INFO} | jq -r .version`
echo "============="

echo "PORTVERSION=${PKG_VERSION}"
echo
echo -n "RUN_DEPENDS= "
echo "${PKG_INFO}" | jq -r '.deps | keys[] as $k | "\($k)>0:\(.[$k] | .origin)"'
echo
echo -n "COMMENT= "
echo "${PKG_INFO}" | jq -r '.comment'

echo "============="

tar -tf "files/${NEW_PKG_NAME}" | egrep -v "\+.*MANIFEST.*" | sed 's|/usr/local/||' > pkg-plist
