#!/usr/bin/env bash
set -e

version=0.0.1
name=buildsh-$version
tar=$name.tar.gz

rm -vf ./buildsh
echo "building ./buildsh from $tar"
(
  set -e
  unset DESTDIR
  tar xf $tar
  cd $name
  ./configure --bindir=/
  make
  DESTDIR=".." make install
  cd ..
  rm -rf $name
) >bootstrap.log 2>&1 || (cat bootstrap.log ; exit 1)

echo "you can now use ./buildsh to build buildsh from the tar archive, ex:"
echo "  ./buildsh $name --configure prefix=/usr --test | bash -e"
