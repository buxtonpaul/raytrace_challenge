cmake_minimum_required(VERSION 3.10)
project(raytrace_challenge)

include(GoogleTest)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Uncomment to enable gprof
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
# SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
# SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")


Message("GTEST_ROOT set to ${GTEST_ROOT}")
find_package(GTest)
find_package(OpenMP)
find_package(PNG REQUIRED)


if(GTest_FOUND)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
set (GTLIBS GTest::GTest GTest::Main)
Message("Using installed GTest")
else()
Message("GTest not found, Downloading")
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
set(GTLIBS gtest_main)
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
            src/modules/material.cpp
            src/modules/light.cpp
            src/modules/world.cpp
            src/modules/camera.cpp
            src/modules/shape.cpp
            src/modules/plane.cpp
            src/modules/pattern.cpp
            src/modules/cube.cpp
            src/modules/cylinder.cpp
            src/modules/group.cpp
            src/modules/triangle.cpp
            src/modules/objparser.cpp
            )


set (TESTS src/tests/tupletests.cpp 
            src/tests/colortests.cpp
            src/tests/canvastests.cpp
            src/tests/utilstests.cpp
            src/tests/matrixtests.cpp
            src/tests/transformationtests.cpp
            src/tests/raytests.cpp
            src/tests/shadertests.cpp
            src/tests/worldtests.cpp
            src/tests/cameratests.cpp
            src/tests/patterntests.cpp
            src/tests/cubetests.cpp
            src/tests/cylindertests.cpp
            src/tests/grouptests.cpp
            src/tests/triangletests.cpp
            src/tests/parsertests.cpp
            )

add_library(rays ${MODULE_SOURCES})
target_link_libraries(rays  OpenMP::OpenMP_CXX ${PNG_LIBRARY})
target_include_directories(rays PUBLIC  src/include ${PNG_INCLUDE_DIR})


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(gtesttest gtesttest.cpp)
target_link_libraries(gtesttest  ${GTLIBS})

# Build the unit tests and add them

add_definitions(-DTEST_DATA_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/testdata/")
add_executable(unittests ${TESTS})
target_include_directories(unittests PUBLIC  "${gtest_SOURCE_DIR}/include" src/include)
target_link_libraries(unittests  ${GTLIBS}  rays)
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

# Build a simple test applicaiton
add_executable(app4 src/app4.cpp)
target_include_directories(app4 PUBLIC src/include)
target_link_libraries(app4 rays)


# Build a simple test applicaiton
add_executable(app5 src/app5.cpp)
target_include_directories(app5 PUBLIC src/include)
target_link_libraries(app5 rays) 

# Build a simple test applicaiton
add_executable(app6 src/app6.cpp)
target_include_directories(app6 PUBLIC src/include)
target_link_libraries(app6 rays) 

# Build a simple test applicaiton
add_executable(app7 src/app7.cpp)
target_include_directories(app7 PUBLIC src/include )
target_link_libraries(app7 rays ) 

# Build a simple test applicaiton
add_executable(objrender src/objrender.cpp)
target_include_directories(objrender PUBLIC src/include )
target_link_libraries(objrender rays ) 