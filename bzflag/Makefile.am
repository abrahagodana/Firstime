SUBDIRS = data doc include man package src
DIST_SUBDIRS = $(SUBDIRS) debian misc tools win32 Dev-C++ BZFlag.xcode

package: FORCE
	cd package && $(MAKE) targets

FORCE:

EXTRA_DIST = \
	autogen.sh \
	BUGS \
	bzflag.info \
	bzflag.lsm \
	bzflag.spec \
	DEVINFO \
	PORTING \
	README.BeOS \
	README.DEVC++ \
	README.IRIX \
	README.Linux \
	README.MINGW32 \
	README.MacOSX \
	README.SDL \
	README.SOLARIS \
	README.UNIX \
	README.WIN32 \
	RELNOTES

MAINTAINERCLEANFILES = \
	aclocal.m4 \
	config.guess \
	config.sub \
	configure \
	bzflag.info \
	bzflag.spec \
	INSTALL \
	install-sh \
	missing \
	mkinstalldirs \
	Makefile.in

debian-cvs: dist
	-rm -rf $(distdir)
	GZIP=$(GZIP_ENV) $(AMTAR)$(TAR) zxf $(distdir).tar.gz
	(cd $(distdir) && debian/buildsnap cvs)

debian-release: debian/changelog dist
	-rm -rf $(distdir)
	GZIP=$(GZIP_ENV) $(AMTAR)$(TAR) zxf $(distdir).tar.gz
	cp debian/changelog $(distdir)/debian/
	(cd $(distdir) && debian/buildsnap release)
