cmake_minimum_required(VERSION 3.6)
project(Utility_AI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES src/actor.cpp src/actor.hpp src/scorer.hpp src/action.hpp src/action.cpp src/decider.cpp src/decider.hpp src/action_data.hpp)
add_library(utility_ai ${SOURCE_FILES})


add_executable(example example/main.cpp)
target_link_libraries(example utility_ai)
