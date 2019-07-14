#!/bin/bash

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ -d build ]; then
   rm -rf build
fi

mkdir build

cd src
make pacman
#make pacman2
cp pacman2.out ../build
cd ..

if [ ! -f build/pacman.out ]; then
    echo 'compile failed'
    exit
fi
if [ ! -f build/pacman2.out ]; then
    echo 'compile failed'
    exit
fi

cd base

python2 capture.py -b myTeam2 -r myTeam -l customCapture
if [ ! $? -eq 0 ]; then
  exit 1
fi
