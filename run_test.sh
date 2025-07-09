#!/bin/bash

echo $(pwd)
socat PTY,link=/dev/ttyS10 PTY,link=/dev/ttyS11 &
sudo socat -d -d PTY,link=/dev/ttyS10,mode=666 PTY,link=/dev/ttyS11,mode=666 &
SOCAT_PID=$!
sleep 1  # Give socat time to create the PTYs

export DEVICE_FILE_1=/dev/ttyS10
export DEVICE_FILE_2=/dev/ttyS11
./test_lins355

# Clean up
sudo kill $SOCAT_PID
sudo rm -f /dev/ttyS10 /dev/ttyS11