#!/bin/bash
DIRECTORY="demo1"

sudo apt source linux
sudo apt install kmod bc cpio flex libelf-dev libssl-dev libncurses5-dev

if [ ! -d "~/$DIRECTORY" ]; then
    mkdir ~/$DIRECTORY
    cd ~/$DIRECTORY && git clone https://github.com/GoblinAlchemist/ldd3
fi

ls /dev/
read x
cd ~/$DIRECTORY/ldd3 && make && cd scull && ./scull_load
ls /dev/

read x

