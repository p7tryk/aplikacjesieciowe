#!/bin/bash

cd ~/
mkdir demo1
cd demo1
rootdir=`pwd`
git clone https://github.com/GoblinAlchemist/ldd3
cd ldd3
cd skull
make
./scull_load
cd /dev/
ls
read x


cd $rootdir
cd ..
