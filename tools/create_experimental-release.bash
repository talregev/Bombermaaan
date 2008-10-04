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
TARGETDIR=./output/Bombermaaan_${VERSION}.${REVISION}e_win32
TARGETZIP=./output/Bombermaaan_${VERSION}.${REVISION}e_win32.zip


#
# Some basic checks
#

if [ -z "$REVISION" ] ; then
    error "Could not find revision string."
fi

if [ -z "$VERSION" ] ; then
    error "Could not find version string."
fi

if [ -e "$TARGETDIR" ] ; then
    error "Target folder '$TARGETDIR' already exists."
fi

if [ -e "$TARGETZIP" ] ; then
    error "Target zip package '$TARGETZIP' already exists."
fi

if [ ! -d ./output ] ; then
    error "Output folder doesn\'t exist. Maybe we are in the wrong directory."
fi


#
# Creating folder
#

echo Creating $RELEASETYPE release package folder for version $VERSION, rev. $REVISION now...

mkdir "$TARGETDIR"                                                          || error "Mkdir ended with return code $?."

mkdir "$TARGETDIR/Levels"                                                   || error "Mkdir ended with return code $?."
cp ../src/_Test_/Release/Levels/L*.TXT "$TARGETDIR/Levels/."                || error "Copy ended with return code $?."

cp ../src/_Test_/Release/Bombermaaan.exe        "$TARGETDIR/."              || error "Copy ended with return code $?."
cp ../src/_Test_/Release/Bombermaaan_32.dll        "$TARGETDIR/."           || error "Copy ended with return code $?."
cp ../src/CHANGELOG.txt        "$TARGETDIR/."                               || error "Copy ended with return code $?."
cp ../COPYING.txt        "$TARGETDIR/."                                     || error "Copy ended with return code $?."
cp ../docs/Readme.html        "$TARGETDIR/."                                || error "Copy ended with return code $?."

cp ../src/_Test_/Release/libogg*.dll            "$TARGETDIR/."              || error "Copy ended with return code $?."
cp ../src/_Test_/Release/libvorbis*.dll         "$TARGETDIR/."              || error "Copy ended with return code $?."
cp ../src/_Test_/Release/SDL*.dll               "$TARGETDIR/."              || error "Copy ended with return code $?."
#smpeg.dll not needed?
#cp ../src/_Test_/Release/smpeg.dll              "$TARGETDIR/."         || error "Copy ended with return code $?."

#
# Creating zip file
#

echo Creating $RELEASETYPE release package for version $VERSION, rev. $REVISION now...

/cygdrive/c/Programme/7-Zip/7z.exe a -tzip "$TARGETZIP" "$TARGETDIR"        || error "7-Zip ended with return code $?."

#
# Checksums
#

echo
echo Checksum MD5:
md5sum "$TARGETZIP" | sed -e 's!\./output/!!'        || error "Md5sum ended with return code $?."

echo Checksum SHA1:
sha1sum "$TARGETZIP" | sed -e 's!\./output/!!'       || error "Sha1sum ended with return code $?."

echo Done.
