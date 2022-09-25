 cmake_minimum_required(VERSION 2.8.12)

 # set(CMAKE_CXX_COMPILER_VERSION 13.0)

 if (APPLE)
   enable_language(OBJC)
   enable_language(OBJCXX)
   option(BUILD_SHARED_LIBS ON)
   option(SGA_BUILD_SFML_FROM_SOURCE ON)
   EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
   # if using m1
   if( ${ARCHITECTURE} STREQUAL "arm64" )
     message( STATUS "Architecture: ${ARCHITECTURE}" )
     set(CMAKE_OSX_ARCHITECTURES "arm64")
   endif()
 endif()

 project(SimpleIdleMiner)

 add_definitions("-std=c++11")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(run run.cpp)
 target_link_libraries(run ${CONAN_LIBS})
