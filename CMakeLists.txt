cmake_minimum_required(VERSION 3.10)
project(ShoeStore CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    main.cpp
    Shoes/*.cpp
    Payment/*.cpp
    Customer/*.cpp
    Order/*.cpp
    OrderDetail/*.cpp
    StockTransaction/*.cpp
)

add_executable(ShoeStore ${SOURCES})

target_include_directories(ShoeStore PRIVATE
    Shoes Payment Customer Order OrderDetail StockTransaction
)

if(NOT MSVC)
    target_compile_options(ShoeStore PRIVATE -Wall -Wextra)
endif()