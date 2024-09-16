#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (C) 2018-2022, Zaryob
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the Lesser GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version. Please read the COPYING file.
#

import sys
import os
import glob
import shutil
import subprocess
from distutils.core import setup, Extension
from distutils.command.install import install

version = '1.6.2'

distfiles = """
    README
    COPYING
    include/common.h
    include/finetune.h
    include/iksemel.h
    src/ikstack.c
    src/utility.c
    src/iks.c
    src/sax.c
    src/dom.c
    src/io-posix.c
    src/sha.c
    src/md5.c
    src/base64.c
    python/pyiks.c
    python/test/*.py
    setup.py
"""

if 'test' in sys.argv:
    import unittest
    test_loader = unittest.TestLoader()
    test_suite = test_loader.discover('python/test/', pattern='*.py')
    if test_suite:
        print("all tests passed :)")
        sys.exit(0)
    sys.exit(1)


class Install(install):
    def finalize_options(self):
        # if os.path.exists("/etc/sulin-release"):
        #    self.install_platlib = '$base/lib/sulin'
        #    self.install_purelib = '$base/lib/sulin'
        install.finalize_options(self)

    def run(self):
        install.run(self)


setup(
    name='iksemel',
    version=version,
    ext_modules=[Extension('iksemel',
                           [
                               'src/ikstack.c',
                               'src/utility.c',
                               'src/iks.c',
                               'src/sax.c',
                               'src/dom.c',
                               'src/io-posix.c',
                               'src/sha.c',
                               'src/md5.c',
                               'src/base64.c',
                               'python/pyiks.c'],
                           define_macros=[('HAVE_STRING_H', '1'),
                                          ('STDC_HEADERS', '1'),
                                          ('HAVE_ERRNO_H', '1')],
                           include_dirs=['/usr/include', './include/'],)],
    cmdclass={
        'install': Install
    }
)
