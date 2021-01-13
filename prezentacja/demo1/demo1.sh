#!/bin/bash
DIRECTORY="demo1"
 
sudo apt source linux
sudo apt install build-essential git make kmod bc cpio flex libelf-dev libssl-dev libncurses5-dev

if [ ! -d "~/$DIRECTORY" ]; then
    mkdir ~/$DIRECTORY
    cd ~/$DIRECTORY && git clone https://github.com/GoblinAlchemist/ldd3
fi

ls /dev/
read x
cd ~/$DIRECTORY/ldd3 && cd scull && make && sudo ./scull_load
ls /dev/

read x

