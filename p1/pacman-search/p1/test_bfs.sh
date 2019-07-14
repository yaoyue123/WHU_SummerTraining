#!/bin/bash

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ -d build ]; then
   rm -rf build
fi

mkdir build

cd src
make bfs
cd ..

if [ ! -f build/bfs.out ]; then
    echo 'compile failed'
    exit
fi

cd base
python2 pacman.py -l tinyMaze -p SearchAgent -a fn=bfs
if [ ! $? -eq 0 ]; then
  exit 1
fi
python2 pacman.py -l mediumMaze -p SearchAgent -a fn=bfs
if [ ! $? -eq 0 ]; then
  exit 1
fi
python2 pacman.py -l bigMaze -z .5 -p SearchAgent -a fn=bfs
if [ ! $? -eq 0 ]; then
  exit 1
fi
echo 'all tests passed'
