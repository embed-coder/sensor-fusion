cmake_minimum_required(VERSION 3.5)

# set the project name
project(sensor-fusion VERSION 0.0.2)

set(
    LINS355_SOURCES
    lins355/LINS355.cpp
)

set(
    CSV_SOURCES
    m2m_csv/m2m_csv.cpp
)

set(CMAKE_INSTALL_RPATH "/usr/local/lib" "/usr/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_library(lins355_static STATIC ${LINS355_SOURCES} ${CSV_SOURCES})

include(CTest)
enable_testing()

# Find header files
find_path(LIBSERIAL_INCLUDE_DIR SerialPort.h PATHS /usr/include/libserial /usr/local/include/libserial)

# Find libraries
find_library(LIBSERIAL_LIBRARIES NAMES serial libserial)


# Include directories
include_directories(
    ${LIBSERIAL_INCLUDE_DIR}
)

# add the executable
add_executable(
    m2m-serial
    
    main.cpp
    ${LINS355_SOURCES}
    ${CSV_SOURCES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set debug flag
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(
    unit_test
)

# Link neccessary libraries, include 3rd libraries
target_link_libraries(
    m2m-serial

    ${LIBSERIAL_LIBRARIES}
    pthread
)