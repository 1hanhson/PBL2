cmake_minimum_required(VERSION 3.10)
project(ShoeStore CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB LIB_SOURCES
    Shoes/*.cpp
    Payment/*.cpp
    Customer/*.cpp
    Order/*.cpp
    OrderDetail/*.cpp
    StockTransaction/*.cpp
)

set(INCLUDE_DIRS Shoes Payment Customer Order OrderDetail StockTransaction)

add_executable(ShoeStore main.cpp ${LIB_SOURCES})
add_executable(RunTests test.cpp ${LIB_SOURCES})

foreach(target ShoeStore RunTests)
    target_include_directories(${target} PRIVATE ${INCLUDE_DIRS})
    if(NOT MSVC)
        target_compile_options(${target} PRIVATE -Wall -Wextra)
    endif()
endforeach()