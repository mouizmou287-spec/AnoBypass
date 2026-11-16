cmake_minimum_required(VERSION 3.10)
project(AnoBypass)

add_library(AnoBypass SHARED main.cpp)

target_link_libraries(AnoBypass
    log
    android
    dl
)
