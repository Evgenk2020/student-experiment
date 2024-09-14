#!/bin/bash

./build/app/bin/st-exp -d 2 2 2 4 5 8 9
echo
./build/app/bin/st-exp -d 2 2 2 4 -- 5 8 9 alf 0.6

exec $SHELL
