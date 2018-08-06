# Process this file with automake to produce Makefile.in
#
# $Id: Makefile.am,v 1.9 2000/12/12 03:26:35 satoru Exp $
#

AUTOMAKE_OPTIONS = 1.4 no-dependencies

lib_LTLIBRARIES    =	libsary.la
libsary_la_SOURCES = 	array.c array.h \
			bsearch.c bsearch.h \
			builder.c builder.h \
			cache.c cache.h \
			i.h \
			ipoint.c ipoint.h \
			merger.c merger.h \
			mkqsort.c mkqsort.h \
			mmap.c mmap.h \
			progress.c progress.h \
			saryconfig.h \
			saryer.c saryer.h \
			sorter.c sorter.h \
			str.c str.h \
			text.c text.h \
			writer.c writer.h \
			version.c

libsary_la_LDFLAGS = 	-version-info $(LTVERSION) -export-dynamic
pkginclude_HEADERS = 	array.h bsearch.h builder.h cache.h i.h ipoint.h \
			merger.h mkqsort.h mmap.h progress.h saryconfig.h \
			saryer.h sorter.h str.h text.h writer.h

INCLUDES = @GLIB_CFLAGS@ -DG_LOG_DOMAIN=\"Sary\" -I$(top_srcdir)
LDADD    = @GLIB_LIBS@

