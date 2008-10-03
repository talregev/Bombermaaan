#!/bin/bash

# Created by Bernd Arnold for Bombermaaan

# Grep the subversion revision number and version string from the CGame.cpp source code file
REVISION=`grep '^#define BOMBERMAAAN_BUILD_STRING ' ../src/Bombermaaan/CGame.cpp | sed -e 's/.* "//' -e 's/".*//'`
VERSION=`grep '^#define BOMBERMAAAN_VERSION_STRING ' ../src/Bombermaaan/CGame.cpp | sed -e 's/.* "//' -e 's/".*//'`

# The 'e' means experimental
TARGETDIR=./output/Bombermaaan_${VERSION}.${REVISION}e_win32
TARGETZIP=./output/Bombermaaan_${VERSION}.${REVISION}e_win32.zip

#
# Some basic checks
#

if [ -z "$REVISION" ] ; then
    echo Could not find revision string. Terminating...
    exit 1
fi

if [ -z "$VERSION" ] ; then
    echo Could not find version string. Terminating...
    exit 2
fi

if [ -e "$TARGETDIR" ] ; then
    echo Target folder already exists. Terminating...
    exit 3
fi

if [ -e "$TARGETZIP" ] ; then
    echo Target zip package already exists. Terminating...
    exit 4
fi

if [ ! -d ./output ] ; then
    echo Output folder doesn\'t exist. Maybe we are in the wrong directory? Terminating...
    exit 5
fi

#
# Creating folder
#

echo Creating experimental release package folder for version $VERSION, rev. $REVISION now...

mkdir "$TARGETDIR"

mkdir "$TARGETDIR/Levels"
cp ../src/_Test_/Release/Levels/L*.TXT "$TARGETDIR/Levels/."

cp ../src/_Test_/Release/Bombermaaan.exe        "$TARGETDIR/."
cp ../src/_Test_/Release/Bombermaaan_32.dll        "$TARGETDIR/."
cp ../src/CHANGELOG.txt        "$TARGETDIR/."
cp ../COPYING.txt        "$TARGETDIR/."
cp ../docs/Readme.html        "$TARGETDIR/."

cp ../src/_Test_/Release/libogg*.dll            "$TARGETDIR/."
cp ../src/_Test_/Release/libvorbis*.dll         "$TARGETDIR/."
cp ../src/_Test_/Release/SDL*.dll               "$TARGETDIR/."
#smpeg.dll not needed?
#cp ../src/_Test_/Release/smpeg.dll              "$TARGETDIR/."

#
# Creating zip file
#

echo Creating experimental release package for version $VERSION, rev. $REVISION now...

/cygdrive/c/Programme/7-Zip/7z.exe a -tzip "$TARGETZIP" "$TARGETDIR"

#
# Checksums
#

echo
echo Checksum MD5:
md5sum "$TARGETZIP"

echo Checksum SHA1:
sha1sum "$TARGETZIP"

echo Done.
