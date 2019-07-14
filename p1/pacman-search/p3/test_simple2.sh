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
  python2 pacman.py -p ReflexAgent -k 2 -l $1
  if [ ! $? -eq 0 ]; then
    exit 1
  fi
}

arr=(openClassic)

for element in ${arr[@]}
do
  run $element
done
