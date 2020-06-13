.. _Introduction:

************
Introduction
************

iksemel is an XML (eXtensible Markup Language) parser library
designed for Jabber applications. It is coded in ANSI C for POSIX
compatible environments, thus highly portable. It is free software
released under the GNU Lesser General Public License.

The purprose of this manual is to tell you how to use the facilities
of the iksemel library. Manual is written with the assumption that you
are familiar with the C programming language, basic programming
concepts, XML and Jabber protocol.

Compiling the Library
=====================

You need to install MinGW (`http://mingw.org <http://mingw.org>`_) under Windows to be able
to compile iksemel. Although not tested by the author, Cygwin should
work equally well.

Library can be built with:

::

  ./configure
  make


If you want to make a self test:

::

  make test


Now you can install it with:

::

  make install


Using iksemel in Applications
=============================

You need to include :file:`iksemel.h` file in your source to access library API.
You can do this with:

`#include "iksemel.h"`

Now you can use iksemel functions and compile your source. In able to link
your compiled object files and generate your executable program, you have to
link with iksemel library. This can be done with:

::

  gcc -o myprg src1.o src2.o src3.o -liksemel


iksemel registers itself with pkg-config while installing, so if you are using
autotools in your program, you can simply check the availability of iksemel
and configure your build process accordingly with:

::

  PKG_CHECK_MODULES(IKSEMEL,iksemel,,exit)


This would result in IKSEMEL_LIBS and IKSEMEL_CFLAGS substitution variables
set to correct values.
