cmake_minimum_required(VERSION 3.8)
project(commute)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BINDIR "${CMAKE_INSTALL_PREFIX}/bin")


include_directories(/usr/local/include
        /usr/local/include/jsoncpp)
link_directories(/usr/local/lib)
link_directories(/usr/local/lib64)

add_subdirectory(src)
