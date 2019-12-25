cmake_minimum_required(VERSION 3.10)
include(GoogleTest)
project(raytrace_challenge)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

enable_testing()

set(MODULE_SOURCES src/modules/tuples.cpp
            src/modules/utils.cpp
            src/modules/color.cpp
            src/modules/canvas.cpp
            src/modules/matrix.cpp
            src/modules/rays.cpp
            src/modules/sphere.cpp
            src/modules/matrix_operators.cpp
            src/modules/tuple_operators.cpp
            )


set (TESTS src/tests/tupletests.cpp 
            src/tests/colortests.cpp
            src/tests/canvastests.cpp
            src/tests/utilstests.cpp
            src/tests/matrixtests.cpp
            src/tests/transformationtests.cpp
            src/tests/raytests.cpp
            )

add_library(rays ${MODULE_SOURCES})
target_include_directories(rays PUBLIC  src/include)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(gtesttest gtesttest.cpp)
target_link_libraries(gtesttest gtest_main)

# Build the unit tests and add them
add_executable(unittests ${TESTS})
target_include_directories(unittests PUBLIC  src/include)
target_link_libraries(unittests gtest_main rays)
gtest_discover_tests(unittests)

# Build a simple test applicaiton
add_executable(app1 src/app1.cpp)
target_include_directories(app1 PUBLIC src/include)
target_link_libraries(app1 rays)

# Build a simple test applicaiton
add_executable(app2 src/app2.cpp)
target_include_directories(app2 PUBLIC src/include)
target_link_libraries(app2 rays)

# Build a simple test applicaiton
add_executable(app3 src/app3.cpp)
target_include_directories(app3 PUBLIC src/include)
target_link_libraries(app3 rays)