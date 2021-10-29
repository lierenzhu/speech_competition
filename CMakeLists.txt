cmake_minimum_required(VERSION 3.16)
project(speech_competition)

set(CMAKE_CXX_STANDARD 14)

add_executable(speech_competition main.cpp speechManager.cpp speechManager.h Speaker.cpp Speaker.h)
