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
SYSTEM=`uname -s`
MACHINE=`uname -m`
if [ "$SYSTEM" = "Linux" ] ; then
    if [ "$MACHINE" = "x86_64" ] ; then
      SYSSUFFIX=linux64
    else
      SYSSUFFIX=linux32
    fi
else
    SYSSUFFIX=win32
fi

# The 'e' means experimental
if [ "$RELEASETYPE" = "experimental" ] ; then
    BASENAME=Bombermaaan_${VERSION}.${REVISION}e_`date '+%Y%m%d'`
else
    BASENAME=Bombermaaan_${VERSION}.${REVISION}_`date '+%Y%m%d'`
fi
TARGETDIR=${BASENAME}_${SYSSUFFIX}
TARGETGZ=${BASENAME}_${SYSSUFFIX}.tar.gz
TARGETZIP=${BASENAME}_${SYSSUFFIX}.zip
SRCTARGETDIR=${BASENAME}_src
SRCTARGETGZ=${BASENAME}_src.tar.gz
SRCTARGETZIP=${BASENAME}_src.zip
RESTARGETDIR=${BASENAME}_res
RESTARGETGZ=${BASENAME}_res.tar.gz
#DXDTARGETDIR=${BASENAME}_doxy
DXDTARGETGZ=${BASENAME}_srcdoc.tar.gz

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
# This check ensures the last modification was less than 10 minutes (600 seconds) ago so we don't forget the update
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

if [ -e "$RESTARGETDIR" ] ; then
    error "Target zip package '$RESTARGETZIP' already exists."
fi

if [ -e "$RESTARGETGZ" ] ; then
    error "Target zip package '$RESTARGETGZ' already exists."
fi

#if [ -e "$DXDTARGETDIR" ] ; then
#    error "Target zip package '$DXDTARGETZIP' already exists."
#fi

if [ -e "$DXDTARGETGZ" ] ; then
    error "Target zip package '$DXDTARGETGZ' already exists."
fi

# Cygwin on WinXP tells "CYGWIN_NT-5.1"
if [ "$SYSTEM" != "Linux" -a "$SYSTEM" != "CYGWIN_NT-5.1" ] ; then
    error "This script was not designed for $SYSTEM."
fi


#############################################################
#
#         Binary release
#
#

#
# Creating folder
#

echo Creating $RELEASETYPE binary release package folder for version $VERSION, rev. $REVISION now...

mkdir "$TARGETDIR"                                                              || error "Mkdir ended with return code $?."

mkdir "$TARGETDIR/Levels"                                                       || error "Mkdir ended with return code $?."
cp ../../src/_Test_/Release/Levels/L*.TXT "$TARGETDIR/Levels/."                 || error "Copy ended with return code $?."

if [ "$SYSTEM" = "Linux" ] ; then
    cp ../../src/Bombermaaan/Bombermaaan        "$TARGETDIR/."                  || error "Copy ended with return code $?."
    strip $TARGETDIR/Bombermaaan                                                || error "Strip ended with return code $?."
else
    if [ "$RELEASETYPE" = "experimental" ] ; then
        # Experimental release: only the 32-pixels version is distributed
        cp ../../src/_Test_/Release/Bombermaaan.exe        "$TARGETDIR/."           || error "Copy ended with return code $?."
        cp ../../src/_Test_/Release/Bombermaaan_32.dll        "$TARGETDIR/."        || error "Copy ended with return code $?."
    else
        # Stable release: distribute both 16- and 32-pixels version
        # The files have to be renamed manually to ..._16.exe and ..._32.exe
        # Build 32-pixels version, rename output file Bombermaaan.exe to Bombermaaan_32.exe
        # Change file STDAFX.H: comment define USE_32_PIXELS_PER_BLOCK and rebuild solution
        # Rename output file Bombermaaan.exe to Bombermaaan_16.exe
        # Run this script again
        cp ../../src/_Test_/Release/Bombermaaan_16.exe        "$TARGETDIR/."        || error "Copy ended with return code $?."
        cp ../../src/_Test_/Release/Bombermaaan_32.exe        "$TARGETDIR/."        || error "Copy ended with return code $?."
        cp ../../src/_Test_/Release/Bombermaaan.dll        "$TARGETDIR/."           || error "Copy ended with return code $?."
        cp ../../src/_Test_/Release/Bombermaaan_32.dll        "$TARGETDIR/."        || error "Copy ended with return code $?."
    fi
fi

cp ../../src/CHANGELOG.txt        "$TARGETDIR/."                                || error "Copy ended with return code $?."
cp ../../COPYING.txt        "$TARGETDIR/."                                      || error "Copy ended with return code $?."
cp ../../docs/Readme.html        "$TARGETDIR/."                                 || error "Copy ended with return code $?."

if [ "$SYSTEM" = "Linux" ] ; then
    cp ../../src/RESGEN/libbombermaaan.so.1.0.0        "$TARGETDIR/."               || error "Copy ended with return code $?."
    ( cd "$TARGETDIR/." ; ln -s libbombermaaan.so.1.0.0 libbombermaaan.so.1 )       || error "Create of symlink ended with return code $?."
    echo -e "#!/bin/sh\nLD_LIBRARY_PATH=. ./Bombermaaan\n" > "$TARGETDIR/run-bm"    || error "Create of start script ended with return code $?."
    chmod u+x "$TARGETDIR/run-bm"                                                   || error "Chmod ended with return code $?."
else
    cp ../../src/_Test_/Release/libogg*.dll            "$TARGETDIR/."               || error "Copy ended with return code $?."
    cp ../../src/_Test_/Release/libvorbis*.dll         "$TARGETDIR/."               || error "Copy ended with return code $?."
    cp ../../src/_Test_/Release/SDL*.dll               "$TARGETDIR/."               || error "Copy ended with return code $?."
fi

#
# Creating zip file
#

echo Creating $RELEASETYPE binary release package for version $VERSION, rev. $REVISION now...

if [ "$SYSTEM" = "Linux" ] ; then
    tar czf "$TARGETGZ" "$TARGETDIR"                                                    || error "Tar ended with return code $?."
else
    /cygdrive/c/Programme/7-Zip/7z.exe a -tzip "$TARGETZIP" "$TARGETDIR" 1> /dev/null   || error "7-Zip ended with return code $?."
fi


#############################################################
#
#         Source release
#
#

#
# Creating folder with source code
#

echo Creating $RELEASETYPE source release package folder for version $VERSION, rev. $REVISION now...

mkdir "$SRCTARGETDIR"                                                           || error "Mkdir ended with return code $?."

mkdir "$SRCTARGETDIR/Bombermaaan"                                               || error "Mkdir ended with return code $?."
cp ../../src/Bombermaaan/*.cpp "$SRCTARGETDIR/Bombermaaan/."                    || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/*.h "$SRCTARGETDIR/Bombermaaan/."                      || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/*.CPP "$SRCTARGETDIR/Bombermaaan/."                    || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/*.H "$SRCTARGETDIR/Bombermaaan/."                      || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/*.rc "$SRCTARGETDIR/Bombermaaan/."                     || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/Makefile "$SRCTARGETDIR/Bombermaaan/."                 || error "Copy ended with return code $?."
cp ../../src/Bombermaaan/Makefile.win "$SRCTARGETDIR/Bombermaaan/."             || error "Copy ended with return code $?."

mkdir "$SRCTARGETDIR/RES"                                                       || error "Mkdir ended with return code $?."
cp ../../src/RES/*.cpp "$SRCTARGETDIR/RES/."                                    || error "Copy ended with return code $?."
cp ../../src/RES/*.h "$SRCTARGETDIR/RES/."                                      || error "Copy ended with return code $?."
cp ../../src/RES/*.CPP "$SRCTARGETDIR/RES/."                                    || error "Copy ended with return code $?."
cp ../../src/RES/*.rc "$SRCTARGETDIR/RES/."                                     || error "Copy ended with return code $?."
cp ../../src/RES/Makefile.win "$SRCTARGETDIR/RES/."                             || error "Copy ended with return code $?."

mkdir "$SRCTARGETDIR/RES32"                                                     || error "Mkdir ended with return code $?."
cp ../../src/RES32/*.cpp "$SRCTARGETDIR/RES32/."                                || error "Copy ended with return code $?."
cp ../../src/RES32/*.h "$SRCTARGETDIR/RES32/."                                  || error "Copy ended with return code $?."
cp ../../src/RES32/*.CPP "$SRCTARGETDIR/RES32/."                                || error "Copy ended with return code $?."
cp ../../src/RES32/*.rc "$SRCTARGETDIR/RES32/."                                 || error "Copy ended with return code $?."
cp ../../src/RES32/Makefile.win "$SRCTARGETDIR/RES32/."                         || error "Copy ended with return code $?."

mkdir "$SRCTARGETDIR/RESGEN"                                                    || error "Mkdir ended with return code $?."
cp ../../src/RESGEN/ResGen.cpp "$SRCTARGETDIR/RESGEN/."                         || error "Copy ended with return code $?."
cp ../../src/RESGEN/ResGen.h "$SRCTARGETDIR/RESGEN/."                           || error "Copy ended with return code $?."
cp ../../src/RESGEN/Makefile "$SRCTARGETDIR/RESGEN/."                           || error "Copy ended with return code $?."

mkdir "$SRCTARGETDIR/third-party"                                               || error "Mkdir ended with return code $?."
rsync -a --exclude '.svn' ../../src/third-party/* "$SRCTARGETDIR/third-party/."                     || error "Rsync ended with return code $?."

cp ../../src/CHANGELOG.txt        "$SRCTARGETDIR/."                             || error "Copy ended with return code $?."
cp ../../src/Makefile        "$SRCTARGETDIR/."                                  || error "Copy ended with return code $?."
cp ../../COPYING.txt        "$SRCTARGETDIR/."                                   || error "Copy ended with return code $?."
cp ../../docs/Readme.html        "$SRCTARGETDIR/."                              || error "Copy ended with return code $?."

#
# Creating zip files from source code folder
#

echo Creating $RELEASETYPE source release package for version $VERSION, rev. $REVISION now...

if [ "$SYSTEM" = "Linux" ] ; then
    zip "$SRCTARGETZIP" "$SRCTARGETDIR"      || error "7-Zip ended with return code $?."
    tar czf "$SRCTARGETGZ" "$SRCTARGETDIR"        || error "Tar ended with return code $?."
else
    /cygdrive/c/Programme/7-Zip/7z.exe a -tzip "$SRCTARGETZIP" "$SRCTARGETDIR" 1> /dev/null      || error "7-Zip ended with return code $?."
    tar czf "$SRCTARGETGZ" "$SRCTARGETDIR"        || error "Tar ended with return code $?."
fi


#############################################################
#
#         Resource release
#
#

#
# Creating folder with resource files
#

echo Creating $RELEASETYPE resource package folder for version $VERSION, rev. $REVISION now...

mkdir "$RESTARGETDIR"                                                           || error "Mkdir ended with return code $?."

mkdir "$RESTARGETDIR/RES"                                                       || error "Mkdir ended with return code $?."
mkdir "$RESTARGETDIR/RES/IMAGE"                                                 || error "Mkdir ended with return code $?."
mkdir "$RESTARGETDIR/RES/SOUND"                                                 || error "Mkdir ended with return code $?."
cp ../../src/RES/IMAGE/*.bmp "$RESTARGETDIR/RES/IMAGE/."                        || error "Copy ended with return code $?."
cp ../../src/RES/SOUND/*.ogg "$RESTARGETDIR/RES/SOUND/."                        || error "Copy ended with return code $?."
cp ../../src/RES/SOUND/*.MOD "$RESTARGETDIR/RES/SOUND/."                        || error "Copy ended with return code $?."
cp ../../src/RES/SOUND/*.S3M "$RESTARGETDIR/RES/SOUND/."                        || error "Copy ended with return code $?."

mkdir "$RESTARGETDIR/RES32"                                                     || error "Mkdir ended with return code $?."
mkdir "$RESTARGETDIR/RES32/IMAGE"                                               || error "Mkdir ended with return code $?."
mkdir "$RESTARGETDIR/RES32/SOUND"                                               || error "Mkdir ended with return code $?."
cp ../../src/RES32/IMAGE/*.bmp "$RESTARGETDIR/RES32/IMAGE/."                    || error "Copy ended with return code $?."
cp ../../src/RES32/SOUND/*.ogg "$RESTARGETDIR/RES32/SOUND/."                    || error "Copy ended with return code $?."
cp ../../src/RES32/SOUND/*.MOD "$RESTARGETDIR/RES32/SOUND/."                    || error "Copy ended with return code $?."
cp ../../src/RES32/SOUND/*.S3M "$RESTARGETDIR/RES32/SOUND/."                    || error "Copy ended with return code $?."

cp ../../src/CHANGELOG.txt        "$RESTARGETDIR/."                             || error "Copy ended with return code $?."
cp ../../COPYING.txt        "$RESTARGETDIR/."                                   || error "Copy ended with return code $?."
cp ../../docs/Readme.html        "$RESTARGETDIR/."                              || error "Copy ended with return code $?."

#
# Creating tar file from resource folder
#

echo Creating $RELEASETYPE resource release package for version $VERSION, rev. $REVISION now...

tar czf "$RESTARGETGZ" "$RESTARGETDIR"        || error "Tar ended with return code $?."


#############################################################
#
#         Documentation
#
#

#
# Creating tar file from doxygen folder
#

echo Creating $RELEASETYPE resource release package for version $VERSION, rev. $REVISION now...

# Delete MD5 and MAP files  first(I don't think we need them)
rm -rf ../../doxygen/output/html/*.md5
rm -rf ../../doxygen/output/html/*.map
tar czf "$DXDTARGETGZ" "../../doxygen/output/html"        || error "Tar ended with return code $?."

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
