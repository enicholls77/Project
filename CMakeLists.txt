 cmake_minimum_required(VERSION 2.8.12)
 project(SimpleIdleMiner)

 add_definitions("-std=c++11")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(idleminer src/main.cpp)
 target_link_libraries(idleminer ${CONAN_LIBS})
