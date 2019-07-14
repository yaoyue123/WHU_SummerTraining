#!/bin/bash

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ -d build ]; then
   rm -rf build
fi

mkdir build

cd src
make dijkstra
cd ..

if [ ! -f build/dijkstra.out ]; then
    echo 'compile failed'
    exit
fi

cd base
python2 pacman.py -l mediumMaze -p SearchAgent -a fn=ucs
if [ ! $? -eq 0 ]; then
  exit 1
fi
python2 pacman.py -l mediumDottedMaze -p StayEastSearchAgent
if [ ! $? -eq 0 ]; then
  exit 1
fi
python2 pacman.py -l mediumScaryMaze -p StayWestSearchAgent
if [ ! $? -eq 0 ]; then
  exit 1
fi
echo 'all tests passed'
