cmake_minimum_required(VERSION 2.8.11)

project(PascalStringOnStack)



include_directories(
    C:/Users/sausingh/Documents/Codeforces/PascalStringOnStack/
    C:/Users/sausingh/Documents/Codeforces/PascalStringOnStack/

)

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS}  ")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" ")

# Define the CXX sources
set ( CXX_SRCS
    main.cpp
)

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g -O0 -Wall -std=c++11")

add_executable(PascalStringOnStack ${CXX_SRCS} ${C_SRCS})

