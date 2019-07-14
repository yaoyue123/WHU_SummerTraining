#!/bin/bash

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ -d build ]; then
   rm -rf build
fi

mkdir build

cd src
make simple
cd ..

if [ ! -f build/simple.out ]; then
    echo 'compile failed'
    exit
fi

cd base

run() {
  python2 pacman.py -p ReflexAgent -k 1 -l $1 -n 10 -q
  if [ ! $? -eq 0 ]; then
    exit 1
  fi
}

arr=(mediumClassic)

for element in ${arr[@]}
do
  run $element
done
