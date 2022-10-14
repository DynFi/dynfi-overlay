PORTNAME=	outline-ss-server
DISTVERSIONPREFIX=      v
DISTVERSION=	1.3.5
PORTREVISION=	1
CATEGORIES=	dynfi
DISTFILES=

MAINTAINER=	oshogbo@DynFi.com
COMMENT=	Outline Shadowsocks server

LICENSE=	APACHE20

USES=   go:modules

USE_GITHUB=yes
GH_ACCOUNT=Jigsaw-Code

GH_TUPLE= \
	golang:protobuf:v1.4.3:golang_protobuf/vendor/github.com/golang/protobuf \
	matttproud:golang_protobuf_extensions:c182affec369:matttproud_golang_protobuf_extensions/vendor/github.com/matttproud/golang_protobuf_extensions \
	protocolbuffers:protobuf-go:v1.27.1:protocolbuffers_protobuf_go/vendor/google.golang.org/protobuf \
	op:go-logging:970db520ece7:golang_go_logging/vendor/github.com/op/go-logging \
	oschwald:geoip2-golang:v1.4.0:oschwald_geoip2_golang/vendor/github.com/oschwald/geoip2-golang \
	oschwald:maxminddb-golang:v1.8.0:oschwald_maxminddb_golang/vendor/github.com/oschwald/maxminddb-golang \
	shadowsocks:go-shadowsocks2:75d43273f5a5:shadowsocks_go_shadowsocks2/vendor/github.com/shadowsocks/go-shadowsocks2 \
	stretchr:testify:v1.6.1:goalng_testify/vendor/github.com/stretchr/testify \
	golang:crypto:9e8e0b390897:golang_crypto/vendor/golang.org/x/crypto \
	golang:sys:4dd72447c267:golang_sys/vendor/golang.org/x/sys \
	go-yaml:yaml:v2.3.0:go_yaml_yaml/vendor/gopkg.in/yaml.v2 \
	beorn7:perks:v1.0.1:beorn7_perks/vendor/github.com/beorn7/perks \
	cespare:xxhash:v2.1.1:cespare_xxhash_v2/vendor/github.com/cespare/xxhash/v2 \
	prometheus:client_golang:v1.7.1:prometheus_client_golang/vendor/github.com/prometheus/client_golang \
	prometheus:client_model:v0.2.0:prometheus_client_model/vendor/github.com/prometheus/client_model \
	prometheus:common:v0.10.0:prometheus_common/vendor/github.com/prometheus/common \
	prometheus:procfs:v0.6.0:prometheus_procfs/vendor/github.com/prometheus/procfs

PLIST_FILES=bin/outline-ss-server

.include <bsd.port.mk>

