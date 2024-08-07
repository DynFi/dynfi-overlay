--- cryptography-41.0.7/src/cryptography/hazmat/bindings/openssl/binding.py	2024-06-19 14:54:55.487411000 +0000
+++ cryptography-41.0.7/src/cryptography/hazmat/bindings/openssl/binding.py	2023-11-28 00:35:35.000000000 +0000
@@ -113,6 +113,15 @@
                 # are ugly legacy, but we aren't going to get rid of them
                 # any time soon.
                 if cls.lib.CRYPTOGRAPHY_OPENSSL_300_OR_GREATER:
+                    if not os.environ.get("CRYPTOGRAPHY_OPENSSL_NO_LEGACY"):
+                        cls._legacy_provider = cls.lib.OSSL_PROVIDER_load(
+                            cls.ffi.NULL, b"legacy"
+                        )
+                        cls._legacy_provider_loaded = (
+                            cls._legacy_provider != cls.ffi.NULL
+                        )
+                        _legacy_provider_error(cls._legacy_provider_loaded)
+
                     cls._default_provider = cls.lib.OSSL_PROVIDER_load(
                         cls.ffi.NULL, b"default"
                     )
