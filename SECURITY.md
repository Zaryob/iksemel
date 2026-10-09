# Security policy

## Scope and support

This repository is a downstream of Gürer Özen's [iksemel](https://github.com/meduketto/iksemel). No version currently has a documented security-support lifetime or a completed security audit. A release tag or a passing parser test suite is not evidence of secure XMPP transport.

The OpenSSL and GnuTLS backends are disabled by default. Their legacy protocol settings and peer-identity verification require further review. Do not rely on them to authenticate an untrusted server or to protect credentials until certificate-chain, hostname, expiry and downgrade rejection tests have been implemented and passed. Building a backend only checks compilation.

XML parsing also processes untrusted input. Applications must enforce their own input-size, time and memory budgets. Sanitizer tests cover exercised inputs only.

## Reporting

Send sensitive reports privately to the maintenance address already listed in the README: **zaryob.dev@gmail.com**. Include the affected commit/version, a minimal reproducer, platform, dependency versions and observed impact. Avoid posting credentials, private captures or an unpatched exploit in a public issue. No response-time guarantee is currently published.

For ordinary build failures or non-sensitive documentation problems, use [GitHub Issues](https://github.com/Zaryob/iksemel/issues).

## Local verification

See [VALIDATION.md](VALIDATION.md) for the commands, observed results and unverified areas. ASan/UBSan runs do not establish certificate validation, protocol correctness or absence of vulnerabilities.
