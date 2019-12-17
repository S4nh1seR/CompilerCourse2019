#!/bin/bash

sudo apt-get install gcc
sudo apt-get install g++
sudo apt-get install cmake
sudo apt-get install cppcheck
bash ./tests/build_bison.sh
bash ./tests/build_flex.sh

