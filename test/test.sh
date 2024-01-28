#!/bin/bash

make clean
clear

if [ "$1" == "all" ]
then
    make test_structure 
    ./test_structure

    make test_distance 
    ./test_distance 
else 
    make "$1" 
    ./"$1" 
fi