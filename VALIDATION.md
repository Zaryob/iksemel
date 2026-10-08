# Local validation record

9 October 2026 (Europe/Istanbul); macOS 27.0 (26A428), Apple M4, 16 GiB RAM, Xcode 27.0 (27A266a), Apple Clang 21.0.0. Runs shared a busy development host; timings are observations, not performance guarantees.

Source baseline: [`6a850e55b7e3e386faed5477757d0bab9aa93aaa`](https://github.com/Zaryob/iksemel/commit/6a850e55b7e3e386faed5477757d0bab9aa93aaa), plus the GnuTLS Meson link fix in this change. Meson 1.12.1; Homebrew OpenSSL 3.6.4 and GnuTLS 3.8.13. This is a local build/parser check, not a completed security audit or a release certification.

| Configuration | Result |
| --- | --- |
| Both TLS backends disabled | 7/7 tests passed |
| Both disabled, address + undefined behavior sanitizers | 7/7 tests passed; no diagnostic in this run |
| OpenSSL enabled, GnuTLS disabled | 9/9 tests passed |
| GnuTLS enabled, OpenSSL disabled | Initially failed to link with redundant `-lgnutls`; 9/9 passed after removing it |

```sh
meson setup build-plain -Dopenssl=disabled -Dgnutls=disabled
meson compile -C build-plain
meson test -C build-plain --print-errorlogs
meson setup build-asan -Dopenssl=disabled -Dgnutls=disabled -Db_sanitize=address,undefined
meson compile -C build-asan
meson test -C build-asan --print-errorlogs
# Point pkg-config at your installed backend dependencies when needed.
meson setup build-openssl -Dopenssl=enabled -Dgnutls=disabled
meson compile -C build-openssl
meson test -C build-openssl --print-errorlogs
meson setup build-gnutls -Dopenssl=disabled -Dgnutls=enabled
meson compile -C build-gnutls
meson test -C build-gnutls --print-errorlogs
```

The macOS run supplied `PKG_CONFIG_PATH=/opt/homebrew/opt/openssl@3/lib/pkgconfig:/opt/homebrew/opt/gnutls/lib/pkgconfig`. It did not change global compiler/linker paths. The backend dependency already supplies the GnuTLS library path; a second bare `-lgnutls` bypassed it and failed on this installation.

Raw command output is retained in [validation/](validation/). Paths are replaced with `<workspace>` and trailing whitespace is removed. Test counts depend on enabled features: the TLS configurations include JID/filter tests, **not certificate or live handshake tests**.

Not verified: certificate-chain/hostname/expiry rejection, downgrade resistance, a modern XMPP server, Python packaging, Windows/Linux builds, fuzz coverage, or release binaries. TLS acceptance gates remain in [#16](https://github.com/Zaryob/iksemel/issues/16). See [SECURITY.md](SECURITY.md) before using untrusted inputs or network transport.
