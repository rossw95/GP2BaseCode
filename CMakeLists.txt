cmake_minimum_required (VERSION 2.8)
project (GP2BaseCode)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)

add_executable(GP2BaseCode src/main.cpp include/Common.h)
include_directories(GP2BaseCode include/ ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
# create the program
target_link_libraries(GP2BaseCode ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} )
