libMac_a_SOURCES =			\
	MacDisplay.cxx			\
	MacDisplay.h			\
	MacMedia.cxx			\
	MacMedia.h			\
	MacPlatformFactory.cxx		\
	MacPlatformFactory.h		\
	MacVisual.cxx			\
	MacVisual.h			\
	MacWindow.cxx			\
	MacWindow.h			\
	SDLMain.h

libMac_a_LIBADD = SDLMain.o

all: SDLMain.o

SDLMain.o:
	$(COMPILE) -c -o $@ `test -f 'SDLMain.m' || echo '$(srcdir)/'`SDLMain.m

AM_CPPFLAGS = $(SDL_CFLAGS) -I$(top_srcdir)/src/platform

if MACOS
if CLIENT_INCLUDED
noinst_LIBRARIES = libMac.a
endif
endif

MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST =				\
	BZFlag-Info.plist		\
	MacBZFlag.icns			\
	SDLMain.m			\
	mkplist.cxx
