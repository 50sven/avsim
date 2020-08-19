#!/bin/bash

help()
{
    echo "usage: ./build.sh [--BUILD_PYTHON]"
    echo "Arguments:"
    echo -e "\t--BUILD_PYTHON : Export library as python package"
}

BUILD_PYTHON=OFF

while [ "$1" != "" ]; do
    case $1 in
        --BUILD_PYTHON) BUILD_PYTHON=ON;;
        -h | --help )   help
                        exit;;
        * )             help
                        exit;;
    esac
    shift
done

echo "============================================"
echo "Start building process"
echo "============================================"

if [ -d "./build" ]
then
    rm -rf build
    echo "Remove and recreate build directory"
fi

mkdir build && cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D BUILD_PYTHON=${BUILD_PYTHON} ..
make

echo "============================================"
echo "End building process"
echo "============================================"