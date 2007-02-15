#!/bin/sh

DISTFILES="AUTHORS CMakeLists.txt COPYING Doxyfile README"
DISTFILES="$DISTFILES mononoke-notify-2.pro src themes"
DISTDIR=mononoke-notify-2
VERSION=`date +%Y%m%d`

rm -rf $DISTDIR ${DISTDIR}_$VERSION.tar.bz2
mkdir $DISTDIR
cp -R $DISTFILES $DISTDIR/
find $DISTDIR/ -name '.svn' | xargs rm -rf
tar -cvjf ${DISTDIR}_$VERSION.tar.bz2 $DISTDIR
rm -rf $DISTDIR