#!/bin/bash
DIRECTORY="demo1"


if [ ! -d "~/$DIRECTORY" ]; then
    mkdir $DIRECTORY
    cd $DIRECTORY && git clone https://github.com/GoblinAlchemist/ldd3
fi

ls /dev/
read x
cd ~/$DIRECTORY/ldd3/skull && make && ./scull_load
ls /dev/

read x

