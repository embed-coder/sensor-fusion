#!/bin/bash
################################################################
# Author: John Nguyen
# Description: Compile LINS355 source code and release bin files
################################################################

OUTPUTDIR=""
VERSION="0.0.1"
BUILDLOG="build.log"

log() {
    echo -e "${@}"  | tee -a ${BUILDLOG}
}

info() {
    echo -e "\033[1m[INFO] \033[0m" $@ | tee -a ${BUILDLOG}
}

error() {
    echo -e "\033[1m[ERROR]\033[0m" $@ | tee -a ${BUILDLOG}
}

warn() {
    echo -e "\033[1m[WARN] \033[0m" $@ | tee -a ${BUILDLOG}
}

rm ${BUILDLOG}

# info "\n\
# ================================================================================\n\
# Start compiling Software and release bin files for LINS355\n\
# Info:\n\
# - 3rd: libserial, googletest\n\
# - Version: ${VERSION}\n\
# ================================================================================\n\
# "
# ask "Are you sure to continue compiling software packages"
# if [ ${?} -ne 0 ]; then
#     exit 4
# fi

info "Start compiling SW"
export LD_LIBRARY_PATH=/usr/lib:/usr/local/lib/

mkdir build
cd build
cmake ..  | tee -a ${BUILDLOG}
make  | tee -a ${BUILDLOG}
mkdir ../release
cp m2m-serial ../
cp unit_test/test_lins355 ../
cd ..
# rm -rf build

info "Run SW by the bin file: m2m-serial"
info "Run unit testing by the bin file: unit_test"