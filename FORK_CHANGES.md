# Downstream scope

This repository retains the history and attribution of Gürer Özen's [iksemel](https://github.com/meduketto/iksemel). It is a maintained downstream, not a new original XML implementation. The LGPL license and original notices are unchanged.

Examples of recorded downstream work (commit history, not a claim that every change has been audited):

- [Fix a crash on certain unicode strings (#11)](https://github.com/Zaryob/iksemel/commit/6a850e55b7e3e386faed5477757d0bab9aa93aaa)
- [Version 1.6.2 (#8)](https://github.com/Zaryob/iksemel/commit/1c93ee10695edbb66698d7de9767650f47c32571)
- [Valgrind tests added in actions](https://github.com/Zaryob/iksemel/commit/367a67e4010137fcae783202f216ddfa52da2370)
- [Unicode translations have been made uchar.h independent.](https://github.com/Zaryob/iksemel/commit/dfa5ba2525054bc880f054b66b77f220835345c9)
- [Merge branch 'silkeh-escape-non-ascii' into dev](https://github.com/Zaryob/iksemel/commit/19c3ec59e6732045c15489a4cb712a771dc3f979)
- [Meson warnings fixed](https://github.com/Zaryob/iksemel/commit/635146f2ab95f1e594d36540c1f5105257414ba3)
- [Fixes on alignment](https://github.com/Zaryob/iksemel/commit/0b3024cf184df18d7b97dfd73a9685bc51325586)
- [Escape non-printable ASCII characters](https://github.com/Zaryob/iksemel/commit/9a5a0b4f3ee7a48e3a812e9ed37ecf441f63f7da)
- [Escape non-ASCII characters](https://github.com/Zaryob/iksemel/commit/f27050677e11fa387d084932bc3ee57957708262)

The 9 October 2026 portfolio change corrects build instructions, removes a redundant GnuTLS linker argument, and publishes the local validation/security limits. It does not upgrade legacy TLS semantics. [VALIDATION.md](VALIDATION.md) separates tested configurations from open transport work. Meson's default project version and the historical 1.6.2 tag are not reconciled by changing or recreating historical tags.
