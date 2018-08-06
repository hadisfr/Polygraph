# Configure paths for sary
# Ryuji Abe	  2000-11-17
#
# This file is a modified version of the
# file glib.m4 that came with glib 1.2.8:
# Configure paths for GLIB
# Owen Taylor     97-11-3

dnl AM_PATH_SARY([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for SARY, and define SARY_CFLAGS and SARY_LIBS
dnl
dnl Example of use (write the following in your 'configure.in'):
dnl AM_PATH_SARY(0.1.0, [LIBS="$LIBS $SARY_LIBS" CFLAGS="$CFLAGS $SARY_CFLAGS"], AC_MSG_ERROR([Can't find sary.]))
dnl
dnl
AC_DEFUN(AM_PATH_SARY,
[dnl 
dnl Get the cflags and libraries from the sary-config script
dnl
AC_ARG_WITH(sary-prefix,[  --with-sary-prefix=PFX   Prefix where SARY is installed (optional)],
            sary_config_prefix="$withval", sary_config_prefix="")
AC_ARG_WITH(sary-exec-prefix,[  --with-sary-exec-prefix=PFX Exec prefix where SARY is installed (optional)],
            sary_config_exec_prefix="$withval", sary_config_exec_prefix="")
AC_ARG_ENABLE(sarytest, [  --disable-sarytest       Do not try to compile and run a test SARY program],
		    , enable_sarytest=yes)

  if test x$sary_config_exec_prefix != x ; then
     sary_config_args="$sary_config_args --sary-prefix=$sary_config_exec_prefix"
     if test x${SARY_CONFIG+set} != xset ; then
        SARY_CONFIG=$sary_config_exec_prefix/bin/sary-config
     fi
  fi
  if test x$sary_config_prefix != x ; then
     sary_config_args="$sary_config_args --prefix=$sary_config_prefix"
     if test x${SARY_CONFIG+set} != xset ; then
        SARY_CONFIG=$sary_config_prefix/bin/sary-config
     fi
  fi

dnl  for module in . $4
dnl  do
dnl      case "$module" in
dnl         gmodule) 
dnl             glib_config_args="$glib_config_args gmodule"
dnl         ;;
dnl         gthread) 
dnl             glib_config_args="$glib_config_args gthread"
dnl         ;;
dnl      esac
dnl  done

  AC_PATH_PROG(SARY_CONFIG, sary-config, no)
  min_sary_version=ifelse([$1], ,0.1.0,$1)
  AC_MSG_CHECKING(for SARY - version >= $min_sary_version)
  no_sary=""
  if test "$SARY_CONFIG" = "no" ; then
    no_sary=yes
  else
    SARY_CFLAGS=`$SARY_CONFIG $sary_config_args --cflags`
    SARY_LIBS=`$SARY_CONFIG $sary_config_args --libs`
    sary_config_major_version=`$SARY_CONFIG $sary_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    sary_config_minor_version=`$SARY_CONFIG $sary_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    sary_config_micro_version=`$SARY_CONFIG $sary_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_sarytest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $SARY_CFLAGS"
      LIBS="$SARY_LIBS $LIBS"
dnl
dnl Now check if the installed SARY is sufficiently new. (Also sanity
dnl checks the results of sary-config to some extent
dnl
      rm -f conf.sarytest
      AC_TRY_RUN([
#include <sary.h>
#include <stdio.h>
#include <stdlib.h>

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.sarytest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = g_strdup("$min_sary_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_sary_version");
     exit(1);
   }

  if ((sary_major_version != $sary_config_major_version) ||
      (sary_minor_version != $sary_config_minor_version) ||
      (sary_micro_version != $sary_config_micro_version))
    {
      printf("\n*** 'sary-config --version' returned %d.%d.%d, but SARY (%d.%d.%d)\n", 
             $sary_config_major_version, $sary_config_minor_version, $sary_config_micro_version,
             sary_major_version, sary_minor_version, sary_micro_version);
      printf ("*** was found! If sary-config was correct, then it is best\n");
      printf ("*** to remove the old version of SARY. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If sary-config was wrong, set the environment variable SARY_CONFIG\n");
      printf("*** to point to the correct copy of sary-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
  else if ((sary_major_version != SARY_MAJOR_VERSION) ||
	   (sary_minor_version != SARY_MINOR_VERSION) ||
           (sary_micro_version != SARY_MICRO_VERSION))
    {
      printf("*** SARY header files (version %d.%d.%d) do not match\n",
	     SARY_MAJOR_VERSION, SARY_MINOR_VERSION, SARY_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     sary_major_version, sary_minor_version, sary_micro_version);
    }
  else
    {
      if ((sary_major_version > major) ||
        ((sary_major_version == major) && (sary_minor_version > minor)) ||
        ((sary_major_version == major) && (sary_minor_version == minor) && (sary_micro_version  >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of SARY (%d.%d.%d) was found.\n",
               sary_major_version, sary_minor_version, sary_micro_version);
        printf("*** You need a version of SARY newer than %d.%d.%d. The latest version of\n",
	       major, minor, micro);
        printf("*** SARY is always available from http://sary.namazu.org.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the sary-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of SARY, but you can also set the SARY_CONFIG environment to point to the\n");
        printf("*** correct copy of sary-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],, no_sary=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CFLAGS="$ac_save_CFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_sary" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$SARY_CONFIG" = "no" ; then
       echo "*** The sary-config script installed by SARY could not be found"
       echo "*** If SARY was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the SARY_CONFIG environment variable to the"
       echo "*** full path to sary-config."
     else
       if test -f conf.sarytest ; then
        :
       else
          echo "*** Could not run SARY test program, checking why..."
          CFLAGS="$CFLAGS $SARY_CFLAGS"
          LIBS="$LIBS $SARY_LIBS"
          AC_TRY_LINK([
#include <sary.h>
#include <stdio.h>
],      [ return ((sary_major_version) || (sary_minor_version) || (sary_micro_version)); ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding SARY or finding the wrong"
          echo "*** version of SARY. If it is not finding SARY, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means SARY was incorrectly installed"
          echo "*** or that you have moved SARY since it was installed. In the latter case, you"
          echo "*** may want to edit the sary-config script: $SARY_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     SARY_CFLAGS=""
     SARY_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(SARY_CFLAGS)
  AC_SUBST(SARY_LIBS)
  rm -f conf.sarytest
])
