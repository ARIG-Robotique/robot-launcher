#!/bin/bash
current_dir=$(pwd=)
cd build/Raspi_64-Release
make clean
make

scp robot-launcher nerell.local:/home/pi

cd ${current_dir}