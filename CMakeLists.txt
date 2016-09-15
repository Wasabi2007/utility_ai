cmake_minimum_required(VERSION 3.6)
project(Utility_AI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

INCLUDE(FindPkgConfig)
pkg_search_module(GLFW REQUIRED glfw3)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(GLEW REQUIRED glew)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})

set(NANO_VG_SOURCES
        extern/nanovg/src/fontstash.h
        extern/nanovg/src/nanovg.c
        extern/nanovg/src/nanovg.h
        extern/nanovg/src/nanovg_gl.h
        extern/nanovg/src/nanovg_gl_utils.h
        extern/nanovg/src/stb_image.h
        extern/nanovg/src/stb_truetype.h
        )

INCLUDE_DIRECTORIES(extern/nanovg/src)
add_library(nano_vg ${NANO_VG_SOURCES})


set(SOURCE_FILES src/actor.cpp src/actor.hpp src/scorer.hpp src/action.hpp src/action.cpp src/decider.cpp src/decider.hpp src/action_data.hpp)
add_library(utility_ai ${SOURCE_FILES})


add_executable(example example/main.cpp)
message(WARNING ${GLEW_STATIC_LIBRARIES})
message(WARNING ${GLFW_STATIC_LIBRARIES})
target_link_libraries(example utility_ai nano_vg ${GLFW_STATIC_LIBRARIES} ${GLEW_STATIC_LIBRARIES})
