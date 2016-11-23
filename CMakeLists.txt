cmake_minimum_required(VERSION 3.2)
project(RobotexLineFollowerCamera)



# PlatformIO build targets
# Must init platformio. See: PlatformIO_CLion_init.txt
add_subdirectory(arduino)





# init Google Test target
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# fake arduino headers
include_directories(test/fake)
# project headers
include_directories(arduino/src)
# gtest headers
include_directories(${gtest_SOURCE_DIR}/include)

add_executable(runTests
        test/fake/Arduino.cpp

        arduino/src/line/Line.h
        arduino/src/line/RowLinePosition.h
        arduino/src/line/RowLinePosition.cpp

        test/src/line/LineTest.cpp
        test/src/line/RowLinePositionTest.cpp
        )

# link
add_subdirectory(test/lib/gtest-1.7.0)
target_link_libraries(runTests gtest_main)



