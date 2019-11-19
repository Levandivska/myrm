cmake_minimum_required(VERSION 3.13)
project(myrm)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS program_options)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
add_executable(myrm main.cpp)
target_link_libraries(myrm ${CMAKE_BOOST_LIBS_INIT} ${Boost_PROGRAM_OPTIONS_LIBRARY})


#
# Macro to find libraries, with support for static-only search
#
#macro(bcl2fastq_find_header_or_die variable file)
#    find_file(${variable} ${file} HINTS ENV C_INCLUDE_PATH ENV CPATH ENV CPLUS_INCLUDE_PATH)
#    if    (${variable})
#        message(STATUS "${file} found as ${${variable}}")
#    else  (${variable})
#        message(FATAL_ERROR "Required header ${file} not found.")
#    endif (${variable})
#endmacro(bcl2fastq_find_header_or_die)

#export C_INCLUDE_PATH =/usr/include/x86_64-linux-gnu
