#!/usr/bin/env bash
set -e

version=0.0.1
name=buildsh-$version
tar=$name.tar.gz

if [ ! -f $tar ] ; then
  echo "downloading $tar"
  curl -L https://github.com/pretorh/buildsh/releases/download/v$version/$tar --output $tar
fi

rm -vf ./buildsh
echo "building ./buildsh from $tar"
unset DESTDIR
tar xf $tar
cd $name
./configure --bindir=/
make
DESTDIR=".." make install
cd ..
rm -rf $name
echo ""
./buildsh --version

echo "you can now use ./buildsh to build buildsh from the tar archive, ex:"
echo "  ./buildsh $name --configure prefix=/usr --test | bash -e"
