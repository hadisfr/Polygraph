# Makefile.in generated automatically by automake 1.4-p5 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/bash

srcdir = .
top_srcdir = ..

prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/sary
pkglibdir = $(libdir)/sary
pkgincludedir = $(includedir)/sary

top_builddir = ..

ACLOCAL = /home/ubuntu/polygraph/dependencies/sary-1.0.4/missing aclocal
AUTOCONF = /home/ubuntu/polygraph/dependencies/sary-1.0.4/missing autoconf
AUTOMAKE = /home/ubuntu/polygraph/dependencies/sary-1.0.4/missing automake
AUTOHEADER = /home/ubuntu/polygraph/dependencies/sary-1.0.4/missing autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = 
host_triplet = x86_64-unknown-linux-gnu
AS = @AS@
CC = gcc-4.9
COPYRIGHT = Copyright (C) 2000-2001 Satoru Takabayashi All rights reserved.
DLLTOOL = @DLLTOOL@
ECHO = echo
EXEEXT = 
GLIB_CFLAGS = -I/usr/include/glib-1.2 -I/usr/lib/glib/include -D_REENTRANT
GLIB_CONFIG = /usr/bin/glib-config
GLIB_LIBS = -L/usr/lib -lgthread -lglib -lpthread
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LTVERSION = 8:1:3
MAINT = #
MAKEINFO = /home/ubuntu/polygraph/dependencies/sary-1.0.4/missing makeinfo
OBJDUMP = @OBJDUMP@
OBJEXT = o
PACKAGE = sary
RANLIB = ranlib
SARY_MAJOR_VERSION = 1
SARY_MICRO_VERSION = 4
SARY_MINOR_VERSION = 0
STRIP = strip
VERSION = 1.0.4

INCLUDES = -I/usr/include/glib-1.2 -I/usr/lib/glib/include -D_REENTRANT -DG_LOG_DOMAIN=\"Sary\" -I$(top_srcdir)
LDADD = -L/usr/lib -lgthread -lglib -lpthread

TESTS = sary-1 sary-2 sary-3 sary-4 sary-5 sary-6 sary-7 sary-8 sary-9\
	mksary-1 mksary-2 mksary-3 mksary-4 mksary-5 \
	array-1 cache-1 cat-1 isearch-1 iso-8859-1 null-1


TEST_CASES = eucjp.txt iso-8859-1.txt null.txt tagged.txt words.txt\
		repeated.txt


TEST_TOOLS = all-substrs.pl byte-indexer.pl gen-icase-data.pl \
		line-indexer.pl sample.pl word-indexer.pl


EXTRA_DIST = $(TESTS) $(TEST_CASES) $(TEST_TOOLS)
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = gtar
GZIP_ENV = --best
all: all-redirect
.SUFFIXES:
$(srcdir)/Makefile.in: # Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu --include-deps tests/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status

tags: TAGS
TAGS:


distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = tests

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
check-TESTS: $(TESTS)
	@failed=0; all=0; \
	srcdir=$(srcdir); export srcdir; \
	for tst in $(TESTS); do \
	  if test -f $$tst; then dir=.; \
	  else dir="$(srcdir)"; fi; \
	  if $(TESTS_ENVIRONMENT) $$dir/$$tst; then \
	    all=`expr $$all + 1`; \
	    echo "PASS: $$tst"; \
	  elif test $$? -ne 77; then \
	    all=`expr $$all + 1`; \
	    failed=`expr $$failed + 1`; \
	    echo "FAIL: $$tst"; \
	  fi; \
	done; \
	if test "$$failed" -eq 0; then \
	  banner="All $$all tests passed"; \
	else \
	  banner="$$failed of $$all tests failed"; \
	fi; \
	dashes=`echo "$$banner" | sed s/./=/g`; \
	echo "$$dashes"; \
	echo "$$banner"; \
	echo "$$dashes"; \
	test "$$failed" -eq 0
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
	$(MAKE) $(AM_MAKEFLAGS) check-TESTS
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am:
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am:
uninstall: uninstall-am
all-am: Makefile
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-generic mostlyclean-am clean-local

clean: clean-am

distclean-am:  distclean-generic clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: tags distdir check-TESTS info-am info dvi-am dvi check check-am \
installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


clean-local:
	rm -rf tmp.*

benchmark: benchmark-search benchmark-mksary

benchmark-search:
	@cp $(top_srcdir)/COPYING tmp.COPYING
	@$(top_srcdir)/src/mksary -q tmp.COPYING
	@for pat in GNU straightforwardly lesser e; do \
		echo PATTERN: $$pat; \
		$(top_srcdir)/src/search-benchmark -n 100000 \
							$$pat tmp.COPYING; \
		echo; \
	done

benchmark-mksary:
	@echo
	@rm -f tmp.garbage
	@target=$(PACKAGE)`date +"-%Y-%m-%d"` && \
	cd $(top_srcdir) && $(MAKE) dist distdir=$$target >/dev/null&& \
	gunzip $$target.tar.gz && \
	mv $$target.tar tests/tmp.garbage
	time $(top_srcdir)/src/mksary -q tmp.garbage
	@echo
	time $(top_srcdir)/src/mksary -q tmp.garbage
	@echo

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
