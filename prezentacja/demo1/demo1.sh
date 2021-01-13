#!/bin/bash
DIRECTORY="demo1"

cd ~/
if [ ! -d "$DIRECTORY" ]; then
    mkdir $DIRECTORY
    cd $DIRECTORY
    git clone https://github.com/GoblinAlchemist/ldd3
fi
cd ldd3
cd skull
pwd
make
./scull_load
cd /dev/
ls
read x


cd ~/
