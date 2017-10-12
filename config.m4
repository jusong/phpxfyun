dnl $Id$
dnl config.m4 for extension xfyun

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(xfyun, for xfyun support,
dnl Make sure that the comment is aligned:
dnl [  --with-xfyun             Include xfyun support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(xfyun, whether to enable xfyun support,
dnl Make sure that the comment is aligned:
[  --enable-xfyun           Enable xfyun support])

if test "$PHP_XFYUN" != "no"; then
  dnl Write more examples of tests here...
  
  dnl # --with-xfyun -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/xfyun.h"  # you most likely want to change this
  dnl if test -r $PHP_XFYUN/$SEARCH_FOR; then # path given as parameter
  dnl   XFYUN_DIR=$PHP_XFYUN
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for xfyun files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       XFYUN_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$XFYUN_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the xfyun distribution])
  dnl fi

  dnl # --with-xfyun -> add include path
  dnl PHP_ADD_INCLUDE($XFYUN_DIR/include)

  dnl # --with-xfyun -> check for lib and symbol presence
  dnl LIBNAME=xfyun # you may want to change this
  dnl LIBSYMBOL=xfyun # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $XFYUN_DIR/lib, XFYUN_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_XFYUNLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong xfyun lib version or lib not found])
  dnl ],[
  dnl   -L$XFYUN_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(XFYUN_SHARED_LIBADD)

  PHP_ADD_INCLUDE(/usr/local/xfyun/include)
  PHP_ADD_LIBRARY(rt, 1, XFYUN_SHARED_LIBADD)
  PHP_ADD_LIBRARY(dl, 1, XFYUN_SHARED_LIBADD)
  PHP_ADD_LIBRARY(pthread, 1, XFYUN_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH(msc, /usr/local/xfyun/lib, XFYUN_SHARED_LIBADD)
  PHP_SUBST(XFYUN_SHARED_LIBADD)

  PHP_NEW_EXTENSION(xfyun, xfyun.c, $ext_shared)
fi
