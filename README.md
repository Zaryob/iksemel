[![Issues](https://img.shields.io/github/issues-raw/Zaryob/iksemel?style=for-the-badge)](https://github.com/Zaryob/iksemel/issues) [![PullRequests](https://img.shields.io/github/issues-pr-raw/Zaryob/iksemel?style=for-the-badge)](https://github.com/Zaryob/iksemel/pulls)

![Language](https://img.shields.io/badge/language-c-blue.svg) ![License](https://img.shields.io/badge/license-LGPL2-purple.svg)

Downstream of [Gürer Özen's iksemel](https://github.com/meduketto/iksemel). See [fork history](FORK_CHANGES.md), [local verification](VALIDATION.md) and [security scope](SECURITY.md). The optional TLS backends are disabled by default and are not security-validated.

                      iksemel (C downstream)

            http://code.google.com/p/iksemel

      Owner:
      Copyright (c) 2000-2011 Gurer Ozen <meduketto at gmail.com>

      Changes and maintenance:
      Copyright (c) 2016-2024 Suleyman Poyraz <zaryob.dev at gmail.com>

Introduction:
-------------

This is an XML parser library mainly designed for Jabber applications.
It provides SAX, DOM, and special Jabber stream APIs. Library is coded
in ANSI C except the network code (which is POSIX compatible), thus
highly portable. Iksemel is released under GNU Lesser General Public
License. A copy of the license is included in the COPYING file.


Requirements:
-------------

Meson >= 0.50.0, Ninja and a C compiler are required to build from Git.

Optional TLS builds use OpenSSL (no minimum is enforced by the build) or GnuTLS >= 3.6.5. Compilation does not establish secure peer verification; read [SECURITY.md](SECURITY.md).

Python bindings are optional and have not been revalidated in this audit. See the Python build files for their dependencies.


Compiling & Install:
--------------------

From a Git checkout, configure the default parser-only build:
```bash
  meson setup build -Dopenssl=disabled -Dgnutls=disabled
```
The Meson version option currently defaults to 1.6; release tags and historical README version strings are separate evidence. No new release is implied here.

Then type
```bash
  meson compile -C build
```
now library is compiled. You can test it with
```bash
  meson test -C build --print-errorlogs
```
and install it with

  (become root if necessary)
```bash
  meson install -C build
```

Parameters
----------

* **openssl**: [enabled,disabled] OpenSSL support. (Conflicts with GNUTLS)
* **gnutls**: [enabled,disabled] GNUTLS support. (Conflicts with OpenSSL)
* **with_tools**: [true,false] Enable Tools (hash, ikslint, iksperf, iksroster)
* **with_python**: [true,false] Enable Python support.
* **tests**: [true,false] Build the regression suite (default: true).

Both TLS features default to disabled. Enable at most one backend explicitly, for example `meson setup build-openssl -Dopenssl=enabled -Dgnutls=disabled`. Tools and Python bindings default to false.
