#!/bin/bash

cd $(dirname $0)

rm -rf build
mkdir build
cd build

cmake ../  \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    $@

make install -j64
