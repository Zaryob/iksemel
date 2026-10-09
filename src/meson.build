sources = [
            'ikstack.c',
            'utility.c',
            'iks.c',
            'sax.c',
            'dom.c',
            'io-posix.c',
            'sha.c',
            'md5.c',
            'base64.c',
           ]

gnutls_sources = ['tls-gnutls.c']
openssl_sources = ['tls-openssl.c']
backend_libs = ''

jabber_sources = [
                  'filter.c',
                  'stream.c',
                  'jabber.c',
                 ]

libiksemel = shared_library('iksemel',
                        sources,
                        include_directories : include_dir,
                        install : true)

if get_option('gnutls').enabled()
  backend_libs += '-lgnutls'
  libiksemel_gnutls = shared_library('iksemel_gnutls',
                          [gnutls_sources],
                          include_directories : include_dir,
                          link_with: libiksemel,
                          dependencies : gnutls_dep,
                          install : true)
endif

if get_option('openssl').enabled()
  # backend_libs += '-lssl -lcrypto'
  libiksemel_openssl = shared_library('iksemel_openssl',
                        openssl_sources,
                        include_directories : include_dir,
                        link_with: libiksemel,
                        dependencies : openssl_dep,
                        install : true)
endif

link_jabber = []
dep_jabber = []

src_jabber = [jabber_sources]
if get_option('gnutls').enabled()
  link_jabber += libiksemel_gnutls
  dep_jabber += gnutls_dep
  src_jabber += gnutls_sources
endif
if get_option('openssl').enabled()
  link_jabber += libiksemel_openssl
  dep_jabber += openssl_dep
  src_jabber += openssl_sources
endif

if backends.length() != 0
  libjabber = shared_library('jabber',
                          src_jabber,
                          include_directories : include_dir,
                          dependencies : dep_jabber,
                          link_with : [libiksemel, link_jabber],
                          install : true)

  # Write pkgconfig of jabber
  jabber_pkgconf = configuration_data()

  jabber_pkgconf.set('prefix', join_paths(get_option('prefix')))
  jabber_pkgconf.set('exec_prefix', '${prefix}')
  jabber_pkgconf.set('includedir', join_paths('${prefix}', get_option('includedir')))
  jabber_pkgconf.set('libdir', join_paths('${prefix}', get_option('libdir')))
  jabber_pkgconf.set('datarootdir', join_paths('${prefix}', get_option('datadir')))
  jabber_pkgconf.set('datadir', '${datarootdir}')
  jabber_pkgconf.set('backend_libs', backend_libs)
  jabber_pkgconf.set('VERSION', version)

  pkg_install_dir = '@0@/pkgconfig'.format(get_option('libdir'))

  configure_file(input : 'jabber.pc.in',
    output : 'jabber-@0@.pc'.format(version),
    configuration : jabber_pkgconf,
    install_dir : pkg_install_dir)
endif
