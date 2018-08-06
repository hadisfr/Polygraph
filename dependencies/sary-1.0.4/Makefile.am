# Process this file with automake to produce Makefile.in
#
# $Id: Makefile.am,v 1.24 2001/06/06 09:05:06 rug Exp $
#

AUTOMAKE_OPTIONS = 1.4 no-dependencies

SUBDIRS = . docs man sary src tests debian

include_HEADERS = sary.h

bin_SCRIPTS = sary-config

m4datadir = $(datadir)/aclocal
m4data_DATA = sary.m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sary.pc

EXTRA_DIST  =	sary.m4 sary.pc.in sary.spec.in sary.spec

##Bug in automake: Can't use `if MAINTAINER_MODE'
@MAINTAINER_MODE_TRUE@include $(srcdir)/maintMakefile

