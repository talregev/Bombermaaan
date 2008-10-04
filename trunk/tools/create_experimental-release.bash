#!/bin/bash

# Created by Bernd Arnold for Bombermaaan


function usage {

    echo "Usage: $0  [ --experimental | --stable | --snapshot ]"
    echo
    echo "Create release packages for Bombermaaan (http://bombermaaan.sourceforge.net/)"
    echo
    echo Parameters:
    echo
    echo "--experimental    Create an experimental release"
    echo "--stable          Create a stable release (not working yet)"
    echo "--snapshot        Create a snapshot release with timestamp as filename (not working yet)"
    echo
    
    exit 1
    
}


function error {

    echo "An error occurred!"
    echo "$1"
    echo "Terminating..."
    
    exit 2
    
}


#
# Parameter check
#

if [ -z "$1" ] ; then
    usage
fi

case "$1" in

    --experimental)
                        RELEASETYPE=experimental
                        ;;
    --stable)
                        # Not working yet
                        usage
                        RELEASETYPE=stable
                        ;;
    --snapshot)
                        # Not working yet
                        usage
                        RELEASETYPE=snapshot
                        ;;
    *)
                        usage
                        ;;

esac


# Grep the subversion revision number and version string from the CGame.cpp source code file
REVISION=`grep '^#define BOMBERMAAAN_BUILD_STRING ' ../src/Bombermaaan/CGame.cpp | sed -e 's/.* "//' -e 's/".*//'`
VERSION=`grep '^#define BOMBERMAAAN_VERSION_STRING ' ../src/Bombermaaan/CGame.cpp | sed -e 's/.* "//' -e 's/".*//'`

# The 'e' means experimental
BASENAME=Bombermaaan_${VERSION}.${REVISION}e_`date '+%Y%m%d'`
TARGETDIR=${BASENAME}_win32
TARGETZIP=${BASENAME}_win32.zip
SRCTARGETDIR=${BASENAME}_src
SRCTARGETGZ=${BASENAME}_src.tar.gz
SRCTARGETZIP=${BASENAME}_src.zip

# Makes friendly names in tar packages when additional directories are skipped from the SRCTARGETDIR variable
cd ./output/.       || error "Cd ended with return code $?."


#
# Some basic checks
#

if [ -z "$REVISION" ] ; then
    error "Could not find revision string."
fi

if [ -z "$VERSION" ] ; then
    error "Could not find version string."
fi

# The build and version strings have to be updated in the file CGame.cpp
# This check ensures the last check was less then 10 minutes (600 seconds) ago so we don't forget the update
LASTCHG=`date '+%s' -r ../../src/Bombermaaan/CGame.cpp`
NOW=`date '+%s'`
let "AGE=NOW-LASTCHG"

if [ "$AGE" -gt 600 ] ; then
    error "File CGame.cpp wasn't modified recently (last update $AGE seconds ago, see BOMBERMAAAN_BUILD_STRING and BOMBERMAAAN_VERSION_STRING)."
fi

if [ -e "$TARGETDIR" ] ; then
    error "Target folder '$TARGETDIR' already exists."
fi

if [ -e "$TARGETZIP" ] ; then
    error "Target zip package '$TARGETZIP' already exists."
fi

if [ -e "$SRCTARGETDIR" ] ; then
    error "Target folder '$SRCTARGETDIR' already exists."
fi

if [ -e "$SRCTARGETZIP" ] ; then
    error "Target zip package '$SRCTARGETZIP' already exists."
fi

if [ -e "$SRCTARGETGZ" ] ; then
    error "Target zip package '$SRCTARGETGZ' already exists."
fi


#
# Creating folder
#

echo Creating $RELEASETYPE release package folder for version $VERSION, rev. $REVISION now...

mkdir "$TARGETDIR"                                                              || error "Mkdir ended with return code $?."

mkdir "$TARGETDIR/Levels"                                                       || error "Mkdir ended with return code $?."
cp ../../src/_Test_/Release/Levels/L*.TXT "$TARGETDIR/Levels/."                 || error "Copy ended with return code $?."

cp ../../src/_Test_/Release/Bombermaaan.exe        "$TARGETDIR/."               || error "Copy ended with return code $?."
cp ../../src/_Test_/Release/Bombermaaan_32.dll        "$TARGETDIR/."            || error "Copy ended with return code $?."
cp ../../src/CHANGELOG.txt        "$TARGETDIR/."                                || error "Copy ended with return code $?."
cp ../../COPYING.txt        "$TARGETDIR/."                                      || error "Copy ended with return code $?."
cp ../../docs/Readme.html        "$TARGETDIR/."                                 || error "Copy ended with return code $?."

cp ../../src/_Test_/Release/libogg*.dll            "$TARGETDIR/."               || error "Copy ended with return code $?."
cp ../../src/_Test_/Release/libvorbis*.dll         "$TARGETDIR/."               || error "Copy ended with return code $?."
cp ../../src/_Test_/Release/SDL*.dll               "$TARGETDIR/."               || error "Copy ended with return code $?."
#smpeg.dll not needed?
#cp ../../src/_Test_/Release/smpeg.dll              "$TARGETDIR/."         || error "Copy ended with return code $?."

#
# Creating zip file
#

echo Creating $RELEASETYPE release package for version $VERSION, rev. $REVISION now...

/cygdrive/c/Programme/7-Zip/7z.exe a -tzip "$TARGETZIP" "$TARGETDIR"            || error "7-Zip ended with return code $?."

#
# Creating folder with source code
#

echo Creating $RELEASETYPE source release package folder for version $VERSION, rev. $REVISION now...

mkdir "$SRCTARGETDIR"                                                           || error "Mkdir ended with return code $?."

mkdir "$SRCTARGETDIR/Bombermaaan"                                               || error "Mkdir ended with return code $?."
cp ../../src/Bombermaaan/*.cpp "$SRCTARGETDIR/Bombermaaan/."                    || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/*.h "$SRCTARGETDIR/Bombermaaan/."                      || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/Makefile "$SRCTARGETDIR/Bombermaaan/."                 || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/Makefile.win "$SRCTARGETDIR/Bombermaaan/."             || error "Copy ended with return code $?."

mkdir "$SRCTARGETDIR/RES"                                                       || error "Mkdir ended with return code $?."
cp ../../src/RES/*.cpp "$SRCTARGETDIR/RES/."                                    || error "Copy ended with return code $?."
cp ../../src/RES/*.h "$SRCTARGETDIR/RES/."                                      || error "Copy ended with return code $?."
cp ../../src/RES/Makefile.win "$SRCTARGETDIR/RES/."                             || error "Copy ended with return code $?."

mkdir "$SRCTARGETDIR/RES32"                                                     || error "Mkdir ended with return code $?."
cp ../../src/RES32/*.cpp "$SRCTARGETDIR/RES32/."                                || error "Copy ended with return code $?."
cp ../../src/RES32/*.h "$SRCTARGETDIR/RES32/."                                  || error "Copy ended with return code $?."
cp ../../src/RES32/Makefile.win "$SRCTARGETDIR/RES32/."                         || error "Copy ended with return code $?."

cp ../../src/CHANGELOG.txt        "$SRCTARGETDIR/."                             || error "Copy ended with return code $?."
cp ../../src/Makefile        "$SRCTARGETDIR/."                                  || error "Copy ended with return code $?."
cp ../../COPYING.txt        "$SRCTARGETDIR/."                                   || error "Copy ended with return code $?."
cp ../../docs/Readme.html        "$SRCTARGETDIR/."                              || error "Copy ended with return code $?."

#
# Creating zip files from source code folder
#

echo Creating $RELEASETYPE source release package for version $VERSION, rev. $REVISION now...

/cygdrive/c/Programme/7-Zip/7z.exe a -tzip "$SRCTARGETZIP" "$SRCTARGETDIR"      || error "7-Zip ended with return code $?."
tar czf "$SRCTARGETGZ" "$SRCTARGETDIR"        || error "Tar ended with return code $?."

#
# Checksums
#

echo
echo Checksums MD5:
md5sum $BASENAME*.*       || error "Md5sum ended with return code $?."

echo
echo Checksums SHA1:
sha1sum $BASENAME*.*      || error "Sha1sum ended with return code $?."

#
# End
#

echo Done.
