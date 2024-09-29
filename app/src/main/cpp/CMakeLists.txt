cmake_minimum_required(VERSION 3.22.1)

project("touchsynth")

add_library(${CMAKE_PROJECT_NAME} SHARED
        jni-interface.cpp
        AudioEngine.cpp
        Synth.cpp)

find_package (oboe REQUIRED CONFIG)

target_link_libraries(${CMAKE_PROJECT_NAME}
    oboe::oboe
    android
    log)
