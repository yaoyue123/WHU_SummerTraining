#!/bin/bash

cd "$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ -d build ]; then
   rm -rf build
fi

mkdir build

cd src
make 2opt
cd ..

if [ ! -f build/2opt.out ]; then
    echo 'compile failed'
    exit
fi

cd base

run() {
  python2 pacman.py -l $1 -p SearchAgent -a fn=opt,prob=FoodSearchProblem
  if [ ! $? -eq 0 ]; then
    exit 1
  fi
}

arr=(testSearch tinyCorners mediumCorners bigCorners tinySearch smallSearch mediumSearch bigSearch boxSearch greedySearch trickySearch)

for element in ${arr[@]}
do
  run $element
done

echo 'all tests passed'
