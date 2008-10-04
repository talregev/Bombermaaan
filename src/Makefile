#
# Makefile for Bombermaaaan
#
#
#
SHELL=/bin/sh


prefix?=/usr/local
exec_prefix=${prefix}
subdirs=third-party RESGEN Bombermaaan
DPKG=dpkg-deb -b
PLATFORM = $(shell uname -m)
ifeq ($(PLATFORM),x86_64)
	PLATFORM=amd64
endif
ifeq ($(PLATFORM),i686)
	PLATFORM=i386
endif
ifeq ($(PLATFORM),i586)
	PLATFORM=i386
endif
VERSION=1.3.2-5
BINFILENAME=Bombermaaan
BIN=Bombermaaan/$(BINFILENAME)
LIBBASENAME=libbombermaaan.so
LIBVERSION=1
LIBREVISION=0.0
LIBFILENAME=$(LIBBASENAME).$(LIBVERSION).$(LIBREVISION)
LIB = RESGEN/$(LIBFILENAME)

RM=rm -f
LN=ln -sf
SED=sed
STRIP=strip

CFLAGS = -O2

all:
	@for i in ${subdirs}; do \
		echo Making all in $$i ; \
		(cd $$i; ${MAKE} all) \
	done

install:
	@for i in ${subdirs}; do \
		echo Installing in $$i ; \
		(cd $$i; ${MAKE} install) \
	done

uninstall:
	@for i in ${subdirs}; do \
		echo Uninstalling in $$i ; \
		(cd $$i; ${MAKE} uninstall) \
	done

depend:
	@for i in ${subdirs}; do \
		echo Depending in $$i ; \
		(cd $$i; ${MAKE} depend) \
	done

debian: debian.deb debian-data.deb
	@echo "Debian Packages were created successfully."

debian.deb: $(BIN)
	cp $(BIN) debian/usr/games/$(BINFILENAME)
	$(STRIP) debian/usr/games/$(BINFILENAME)
	sed -e 's/ARCHITECTURE/$(PLATFORM)/' debian/DEBIAN/control.dist > debian/DEBIAN/control
	chmod 755 debian/DEBIAN/post*
	chmod 755 md5sum.pl
	(cd debian; ../md5sum.pl)
	$(DPKG) debian bombermaaan_$(VERSION)_$(PLATFORM).deb

debian-data.deb: $(LIB)
	cp $(LIB) debian-data/usr/lib/$(LIBFILENAME)
	(cd debian-data/usr/lib; $(LN) $(LIBFILENAME) $(LIBBASENAME); $(LN) $(LIBFILENAME) $(LIBBASENAME).$(LIBVERSION))
	sed -e 's/ARCHITECTURE/$(PLATFORM)/' debian-data/DEBIAN/control.dist > debian-data/DEBIAN/control
	chmod 755 debian/DEBIAN/post*
	chmod 755 md5sum.pl
	(cd debian-data; ../md5sum.pl)
	$(DPKG) debian-data bombermaaan-data_$(VERSION)_$(PLATFORM).deb

clean:
	@for i in ${subdirs}; do \
		echo Cleaning in $$i ; \
		(cd $$i; ${MAKE} clean) \
	done
	$(RM) debian/usr/games/$(BIN)
	$(RM) debian-data/usr/lib/$(LIBFILENAME) debian-data/usr/lib/$(LIBBASENAME) debian-data/usr/lib/$(LIBBASENAME).$(LIBVERSION)
	$(RM) debian/DEBIAN/control debian-data/DEBIAN/control
	$(RM) bombermaaan_$(VERSION)_$(PLATFORM).deb bombermaaan-data_$(VERSION)_$(PLATFORM).deb

distclean: clean
	$(RM) .tm_project2.cache

