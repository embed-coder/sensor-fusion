#!/bin/bash
################################################################
# Author: John Nguyen
# Description: Compile LINS355 source code and release bin files
################################################################

OUTPUTDIR=""
VERSION="0.0.2"
BUILDLOG="${PWD}/build.log"

log() {
    echo -e "${@}"  | tee -a ${BUILDLOG}
}

info() {
    echo -e "\e[36m[INFO]" ${@}"\e[0m" | tee >(sed 's/\x1b\[[0-9;]*m//g' >> ${BUILDLOG})
}

error() {
    echo -e "\e[31m[ERROR]" ${@}"\e[0m" | tee >(sed 's/\x1b\[[0-9;]*m//g' >> ${BUILDLOG})
}

warn() {
    echo -e "\e[33m[WARN]" ${@}"\e[0m" | tee >(sed 's/\x1b\[[0-9;]*m//g' >> ${BUILDLOG})
}

ask()
{
    echo -en "\e[35m${1} (y/n)?\e[0m "
    while [ 1 ]; do
        read CHOICE
        case "${CHOICE}" in 
            y|Y ) 
                return 0
                ;;
            n|N )
                return 1
                ;;
            * ) 
                echo "invalid";;
        esac
    done
}


rm ${BUILDLOG}

info "\n\
================================================================================\n\
Start compiling Sensor Fusion and release bin files\n\
Info:\n\
- 3rd: libserial, googletest\n\
- Version: ${VERSION}\n\
- Log: ${BUILDLOG}\n\
================================================================================\n\
"

# ask "Are you sure to continue compiling software packages"
# if [ ${?} -ne 0 ]; then
#     exit 4
# fi

export LD_LIBRARY_PATH=/usr/lib:/usr/local/lib/

mkdir build
cd build
cmake .. 2>&1 | tee -a ${BUILDLOG}
make 2>&1 | tee -a ${BUILDLOG}
mkdir ../release
cp m2m-serial ../
cp unit_test/test_lins355 ../
cd ..
# rm -rf build

info "\n\
================================================================================\n\
The compiling process is done, please refer to README file for how to test!\n\
================================================================================\n\
"