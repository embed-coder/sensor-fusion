#!/bin/bash
################################################################
# Author: John Nguyen
# Description: Helper script for building and release Software
################################################################

BINARYFILES="m2m-serial test_lins355"
BUILDDIR="build"
BUILDLOG="${PWD}/build.log"
BUILDTYPE=""
OUTPUTDIR=""
RELEASEDIR="release"
VERSION="0.0.2"

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

error() {
    echo -e "\e[31m[ERROR]" ${@}"\e[0m" | tee >(sed 's/\x1b\[[0-9;]*m//g' >> ${BUILDLOG})
}

info() {
    echo -e "\e[36m[INFO]" ${@}"\e[0m" | tee >(sed 's/\x1b\[[0-9;]*m//g' >> ${BUILDLOG})
}

log() {
    echo -e "${@}"  | tee -a ${BUILDLOG}
}

warn() {
    echo -e "\e[33m[WARN]" ${@}"\e[0m" | tee >(sed 's/\x1b\[[0-9;]*m//g' >> ${BUILDLOG})
}

help() {
  echo -e "Version: ${VERSION}, created by John Nguyen\n"
  # `cat << EOF` This means that cat should stop reading when EOF is detected
  cat << EOF
Helper script for build and compiling sensor_fusion.

Usage: ${0} [OPTIONS]

  -a, --all                 Build the whole firmware's package.

  -c, --clean               Clean all previous compiled files and directories.

  -C, --core      <number>  Number of core used to run the compiling process.
                            - If no input, the maximum number of cores on current machine will be used.

  -F, --folder    <path>    Input the path to folder contains released packages after build.
                            - If no input, default is "release" folder.

  -h, --help                Display this help

  -p, --package   <name>    Specify the name package need to build.
                            - If no input, script exits.

  -t, --thread    <number>  Number of threads can run. The more thread, the faster compiling process running.
                            - If no input, default is number of core.

  -v, -version,             Version credit info.

  -V, --verbose             Run script in verbose mode. Will print messages each step of execution.
                            - Set xtrace and verbose mode by command "set -xv"

Example:
# Clean all and rebuild again
  ${0} -ca
# Re-build the whole firmware without cleaning
  ${0} -a
# Re-build only specific package
  ${0} -p <package_name>
EOF
  # EOF is found above and hence cat command stops reading. This is equivalent to echo but much neater when printing out.
}

version() {
  echo -e "Version: ${VERSION}, created on by John Nguyen.\n"
}

# Parsing arguments from console
OPTIONS=$(getopt -l all,clean,core:,folder:,help,package:,thread:,version,verbose -- acC:f:hp:t:vV "$@") || exit 1
eval set -- "$OPTIONS"
while true; do
  case "$1" in
  -a|--all) BUILDTYPE="all"; shift;;
  -c|--clean) CLEAN=1; shift;;
  -C|--core) CORE=${2}; shift 2;;
  -F|--folder) FOLDER=${2}; shift 2;;
  -h|--help) help; exit 0;;
  -p|--package) BUILDTYPE="package" && PACKAGE=${2}; shift 2;;
  -t|--thread) THREAD=${2}; shift 2;;
  -v|--version) version; exit 0;;
  -V|--verbose) VERBOSE=1; set -xv; shift;;
  --) shift; break;;
  *) echo Error; exit 1;;
  esac
done

if [ ${CLEAN} -eq 1 ]; then
  ask "Are you sure to continue cleaning the previous build and releases"
  if [ ${?} -ne 0 ]; then
      exit 4
  fi
  rm -rf ${BINARYFILES} ${BUILDDIR} ${BUILDLOG} ${RELEASEDIR}
  info "Project was cleaned!"
  if [ "${BUILDTYPE}" == "" ]; then
    exit 0
  fi
fi

rm ${BUILDLOG}

info "\n\
================================================================================\n\
Start compiling Sensor Fusion and release bin files\n\
Info:\n\
- 3rd: libserial, googletest\n\
- Version: ${VERSION}\n\
- Build type: ${BUILDTYPE}\n\
- Log: ${BUILDLOG}\n\
================================================================================\n\
"

export LD_LIBRARY_PATH=/usr/lib:/usr/local/lib/

if [ "${BUILDTYPE}" == "all" ]; then
  mkdir ${BUILDDIR}
  cd ${BUILDDIR}
  cmake .. 2>&1 | tee -a ${BUILDLOG}
  make 2>&1 | tee -a ${BUILDLOG}
  mkdir "../${RELEASEDIR}"
  cp m2m-serial ../
  cp unit_test/test_lins355 ../
  # cd ..
fi

if [ ${?} -ne 0 ]; then
  error "\n\
================================================================================\n\
The compiling process error, please check the log for more detail!\n\
================================================================================\n\
  "
  exit 4
fi

info "\n\
================================================================================\n\
The compiling process is done, please refer to README file for how to test!\n\
================================================================================\n\
"