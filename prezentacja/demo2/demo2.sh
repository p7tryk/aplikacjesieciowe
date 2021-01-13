#!/bin/bash

cd ~/
mkdir demo1 && cd demo1
rootdir=`pwd`
git clone https://github.com/GoblinAlchemist/ldd3
cd scull
make
./scull_load
cd /dev/
ls



cd $rootdir
cd ..
