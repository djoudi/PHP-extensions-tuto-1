dnl $Id$
dnl config.m4 for extension tutodvp1

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(tutodvp1, for tutodvp1 support,
dnl Make sure that the comment is aligned:
dnl [  --with-tutodvp1             Include tutodvp1 support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(tutodvp1, whether to enable tutodvp1 support,
dnl Make sure that the comment is aligned:
[  --enable-tutodvp1           Enable tutodvp1 support])

if test "$PHP_TUTODVP1" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-tutodvp1 -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/tutodvp1.h"  # you most likely want to change this
  dnl if test -r $PHP_TUTODVP1/$SEARCH_FOR; then # path given as parameter
  dnl   TUTODVP1_DIR=$PHP_TUTODVP1
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for tutodvp1 files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TUTODVP1_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TUTODVP1_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the tutodvp1 distribution])
  dnl fi

  dnl # --with-tutodvp1 -> add include path
  dnl PHP_ADD_INCLUDE($TUTODVP1_DIR/include)

  dnl # --with-tutodvp1 -> check for lib and symbol presence
  dnl LIBNAME=tutodvp1 # you may want to change this
  dnl LIBSYMBOL=tutodvp1 # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TUTODVP1_DIR/lib, TUTODVP1_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TUTODVP1LIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong tutodvp1 lib version or lib not found])
  dnl ],[
  dnl   -L$TUTODVP1_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TUTODVP1_SHARED_LIBADD)

  PHP_NEW_EXTENSION(tutodvp1, tutodvp1.c, $ext_shared)
fi
