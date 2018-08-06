# Makefile.in generated automatically by automake 1.4-p5 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

# Process this file with automake to produce Makefile.in
#
# $Id: Makefile.am,v 1.9 2001/12/24 14:10:37 satoru Exp $
#


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

AUTOMAKE_OPTIONS = 1.4 no-dependencies

bin_PROGRAMS = sary mksary

INCLUDES = -I/usr/include/glib-1.2 -I/usr/lib/glib/include -D_REENTRANT -DG_LOG_DOMAIN=\"Sary\" -I$(top_srcdir)
LDADD = $(top_builddir)/sary/libsary.la -L/usr/lib -lgthread -lglib -lpthread

sary_SOURCES = sary.c getopt.h getopt.c getopt1.c

mksary_SOURCES = mksary.c getopt.h getopt.c getopt1.c

noinst_PROGRAMS = isearch-test cache-test cat-test search-benchmark\
			repeated-test


cache_test_SOURCES = cache-test.c

cat_test_SOURCES = cat-test.c

isearch_test_SOURCES = isearch-test.c

repeated_test_SOURCES = repeated-test.c

search_benchmark_SOURCES = search-benchmark.c \
				getopt.h getopt.c getopt1.c

mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
bin_PROGRAMS =  sary$(EXEEXT) mksary$(EXEEXT)
noinst_PROGRAMS =  isearch-test$(EXEEXT) cache-test$(EXEEXT) \
cat-test$(EXEEXT) search-benchmark$(EXEEXT) repeated-test$(EXEEXT)
PROGRAMS =  $(bin_PROGRAMS) $(noinst_PROGRAMS)


DEFS = -DHAVE_CONFIG_H -I. -I$(srcdir) -I..
CPPFLAGS = 
LDFLAGS = 
LIBS = 
sary_OBJECTS =  sary.$(OBJEXT) getopt.$(OBJEXT) getopt1.$(OBJEXT)
sary_LDADD = $(LDADD)
sary_DEPENDENCIES =  $(top_builddir)/sary/libsary.la
sary_LDFLAGS = 
mksary_OBJECTS =  mksary.$(OBJEXT) getopt.$(OBJEXT) getopt1.$(OBJEXT)
mksary_LDADD = $(LDADD)
mksary_DEPENDENCIES =  $(top_builddir)/sary/libsary.la
mksary_LDFLAGS = 
isearch_test_OBJECTS =  isearch-test.$(OBJEXT)
isearch_test_LDADD = $(LDADD)
isearch_test_DEPENDENCIES =  $(top_builddir)/sary/libsary.la
isearch_test_LDFLAGS = 
cache_test_OBJECTS =  cache-test.$(OBJEXT)
cache_test_LDADD = $(LDADD)
cache_test_DEPENDENCIES =  $(top_builddir)/sary/libsary.la
cache_test_LDFLAGS = 
cat_test_OBJECTS =  cat-test.$(OBJEXT)
cat_test_LDADD = $(LDADD)
cat_test_DEPENDENCIES =  $(top_builddir)/sary/libsary.la
cat_test_LDFLAGS = 
search_benchmark_OBJECTS =  search-benchmark.$(OBJEXT) getopt.$(OBJEXT) \
getopt1.$(OBJEXT)
search_benchmark_LDADD = $(LDADD)
search_benchmark_DEPENDENCIES =  $(top_builddir)/sary/libsary.la
search_benchmark_LDFLAGS = 
repeated_test_OBJECTS =  repeated-test.$(OBJEXT)
repeated_test_LDADD = $(LDADD)
repeated_test_DEPENDENCIES =  $(top_builddir)/sary/libsary.la
repeated_test_LDFLAGS = 
CFLAGS = -g -O2 -Wall -Wunused -Wuninitialized -Wmissing-prototypes -Wmissing-declarations
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --mode=compile $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = gtar
GZIP_ENV = --best
SOURCES = $(sary_SOURCES) $(mksary_SOURCES) $(isearch_test_SOURCES) $(cache_test_SOURCES) $(cat_test_SOURCES) $(search_benchmark_SOURCES) $(repeated_test_SOURCES)
OBJECTS = $(sary_OBJECTS) $(mksary_OBJECTS) $(isearch_test_OBJECTS) $(cache_test_OBJECTS) $(cat_test_OBJECTS) $(search_benchmark_OBJECTS) $(repeated_test_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .lo .o .obj .s
$(srcdir)/Makefile.in: # Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu src/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


mostlyclean-binPROGRAMS:

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

distclean-binPROGRAMS:

maintainer-clean-binPROGRAMS:

install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(LIBTOOL)  --mode=install $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`"; \
	    $(LIBTOOL)  --mode=install $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	list='$(bin_PROGRAMS)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	done

mostlyclean-noinstPROGRAMS:

clean-noinstPROGRAMS:
	-test -z "$(noinst_PROGRAMS)" || rm -f $(noinst_PROGRAMS)

distclean-noinstPROGRAMS:

maintainer-clean-noinstPROGRAMS:

.c.o:
	$(COMPILE) -c $<

# FIXME: We should only use cygpath when building on Windows,
# and only if it is available.
.c.obj:
	$(COMPILE) -c `cygpath -w $<`

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core
	-rm -f *.$(OBJEXT)

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

.c.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

.s.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

.S.lo:
	$(LIBTOOL) --mode=compile $(COMPILE) -c $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:

maintainer-clean-libtool:

sary$(EXEEXT): $(sary_OBJECTS) $(sary_DEPENDENCIES)
	@rm -f sary$(EXEEXT)
	$(LINK) $(sary_LDFLAGS) $(sary_OBJECTS) $(sary_LDADD) $(LIBS)

mksary$(EXEEXT): $(mksary_OBJECTS) $(mksary_DEPENDENCIES)
	@rm -f mksary$(EXEEXT)
	$(LINK) $(mksary_LDFLAGS) $(mksary_OBJECTS) $(mksary_LDADD) $(LIBS)

isearch-test$(EXEEXT): $(isearch_test_OBJECTS) $(isearch_test_DEPENDENCIES)
	@rm -f isearch-test$(EXEEXT)
	$(LINK) $(isearch_test_LDFLAGS) $(isearch_test_OBJECTS) $(isearch_test_LDADD) $(LIBS)

cache-test$(EXEEXT): $(cache_test_OBJECTS) $(cache_test_DEPENDENCIES)
	@rm -f cache-test$(EXEEXT)
	$(LINK) $(cache_test_LDFLAGS) $(cache_test_OBJECTS) $(cache_test_LDADD) $(LIBS)

cat-test$(EXEEXT): $(cat_test_OBJECTS) $(cat_test_DEPENDENCIES)
	@rm -f cat-test$(EXEEXT)
	$(LINK) $(cat_test_LDFLAGS) $(cat_test_OBJECTS) $(cat_test_LDADD) $(LIBS)

search-benchmark$(EXEEXT): $(search_benchmark_OBJECTS) $(search_benchmark_DEPENDENCIES)
	@rm -f search-benchmark$(EXEEXT)
	$(LINK) $(search_benchmark_LDFLAGS) $(search_benchmark_OBJECTS) $(search_benchmark_LDADD) $(LIBS)

repeated-test$(EXEEXT): $(repeated_test_OBJECTS) $(repeated_test_DEPENDENCIES)
	@rm -f repeated-test$(EXEEXT)
	$(LINK) $(repeated_test_LDFLAGS) $(repeated_test_OBJECTS) $(repeated_test_LDADD) $(LIBS)

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags $(ETAGS_ARGS) $$tags  $$unique $(LISP) -o $$here/TAGS)

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = src

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
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am: install-binPROGRAMS
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-binPROGRAMS
uninstall: uninstall-am
all-am: Makefile $(PROGRAMS)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(bindir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-binPROGRAMS mostlyclean-noinstPROGRAMS \
		mostlyclean-compile mostlyclean-libtool \
		mostlyclean-tags mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-binPROGRAMS clean-noinstPROGRAMS clean-compile \
		clean-libtool clean-tags clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-binPROGRAMS distclean-noinstPROGRAMS \
		distclean-compile distclean-libtool distclean-tags \
		distclean-generic clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-binPROGRAMS \
		maintainer-clean-noinstPROGRAMS \
		maintainer-clean-compile maintainer-clean-libtool \
		maintainer-clean-tags maintainer-clean-generic \
		distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: mostlyclean-binPROGRAMS distclean-binPROGRAMS clean-binPROGRAMS \
maintainer-clean-binPROGRAMS uninstall-binPROGRAMS install-binPROGRAMS \
mostlyclean-noinstPROGRAMS distclean-noinstPROGRAMS \
clean-noinstPROGRAMS maintainer-clean-noinstPROGRAMS \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile mostlyclean-libtool distclean-libtool \
clean-libtool maintainer-clean-libtool tags mostlyclean-tags \
distclean-tags clean-tags maintainer-clean-tags distdir info-am info \
dvi-am dvi check check-am installcheck-am installcheck install-exec-am \
install-exec install-data-am install-data install-am install \
uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


# Memory leak checking. It requires mpatrol 
# <http://www.cbmamiga.demon.co.uk/mpatrol/>
# LDFLAGS is set for Linux.
mleak-check:
	@echo -n "recompiling for memory leak checking: "
	@cd .. && make clean  >/dev/null 2>&1 && \
	make LDFLAGS='-lmpatrol -lbfd -liberty' >/dev/null 2>&1
	@echo done

	@echo foo > foo

	@echo -n "checking mksary: "

	@MPATROL_OPTIONS="LOGALL PROF USEDEBUG" ./mksary -b0 foo >/dev/null

	@# Ignore memory leaks caused by pthread_create.
	@perl -n00e 'print unless /pthread_create/' \
		mpatrol.log >mpatrol2.log	
	@mleak mpatrol2.log | grep -q 'unfreed allocations: 0 ' && echo ok

	@echo -n "checking sary: "

	@MPATROL_OPTIONS="LOGALL PROF USEDEBUG" ./sary foo foo > /dev/null

	@# Ignore memory leaks caused by setlocale.
	@perl -n00e 'print unless /setlocale/' \
		mpatrol.log >mpatrol2.log	
	@mleak mpatrol2.log | grep -q 'unfreed allocations: 0 ' && echo ok

	@rm -f foo foo.ary mpatrol.log mpatrol2.log

	@echo -n "recompiling for normal use: "
	@cd .. && make clean  >/dev/null 2>&1 && make >/dev/null 2>&1
	@echo done

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
