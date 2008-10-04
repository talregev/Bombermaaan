#
# Makefile for Bombermaaaan: third-party
#
#
#
subdirs=tinyxml

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

clean:
	@for i in ${subdirs}; do \
		echo Cleaning in $$i ; \
		(cd $$i; ${MAKE} clean) \
	done

distclean: clean

