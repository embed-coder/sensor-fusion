#!/bin/bash

echo $(pwd)
socat PTY,link=/dev/ttyS10 PTY,link=/dev/ttyS11 &
export DEVICE_FILE_1=/dev/ttyS10
export DEVICE_FILE_2=/dev/ttyS11
./test_lins355

killall socat