cmake_minimum_required(VERSION 3.6)
project(Utility_AI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp src/actor.cpp src/actor.hpp src/scorer.hpp src/action.hpp src/action.cpp src/decider.cpp src/decider.hpp src/action_data.hpp)
add_executable(Utility_AI ${SOURCE_FILES})