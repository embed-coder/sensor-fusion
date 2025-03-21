#!/bin/bash

TEST_CASE="${1}"
TEST_DATA_FILE="${2}"
# ex: /dev/ttyUSB1
SERIAL_DEVICE="${3}"

case "${1}" in
    LINS355_Device_OK) echo -n -e "\x4C\x53\x53\x30\x1E\x00\x29\x00\x2D\xF3\x3E\x00\x02\xFF\xFE\xFF\xFC\xFD\xB6\xFA\x34\x05\x17\x1E\x74\x1E\x74\x1E\x74\x1E\x74\x29\xF6\x00\x00\x01\x25" > ${SERIAL_DEVICE};;
    FAIL_CRC) echo -n -e "\x4C\x53\x53\x30\x1E\x00\x29\x00\x2D\xF3\x3E\x00\x02\xFF\xFE\xFF\xFC\xFD\xB6\xFA\x34\x05\x17\x1E\x74\x1E\x74\x1E\x74\x1E\x74\x29\xF6\x00\x01\x01\x25" > ${SERIAL_DEVICE};;
    FAIL_DataFile_Invalid_Column_Name) sudo rm -f ${TEST_DATA_FILE}; echo -e "Timestamp,Acc,Acc_y,Acc_z\n" > ${TEST_DATA_FILE};;
    FAIL_DataFile_Non_Existing) sudo rm -f ${TEST_DATA_FILE};;
    --) break;;
    *) echo -e "Error: incorrect parameters\nParameter is OK or FAIL_CRC"; exit 1;;
esac