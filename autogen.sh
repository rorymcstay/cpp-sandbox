#!/bin/bash

cd $(dirname $0)

echo "Clearing build data"
rm -rf build
mkdir build
cd build

echo "Passing $@"

cmake ../  \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    "$@"

make install -j64
