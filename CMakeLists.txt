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
 set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#  add_definitions("-std=c++11")
 set(CMAKE_CXX_STANDARD 14)

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()


 aux_source_directory(src/ sources)
 add_executable(idleminer ${sources})
 target_link_libraries(idleminer ${CONAN_LIBS})

 enable_testing()

 aux_source_directory(test/integration inttests)

 add_executable(
  integration_tests
  src/Tool.cpp
  src/HandTool.cpp
  src/Worker.cpp
  src/Game.cpp
  ${inttests}
 )

target_link_libraries(
  integration_tests
  ${CONAN_LIBS}
  # GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(integration_tests)
