#!/bin/bash

mkdir demo1 && cd demo1
rootdir=`pwd`
git clone https://github.com/martinezjavier/ldd3/pull/60/commits/ac573e18e05e7a98ea58f153194bda1057c31779
cd scull
make
./scull_load
cd /dev/
ls



cd $rootdir
cd ..
