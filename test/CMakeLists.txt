cmake_minimum_required(VERSION 3.2)
project(RobotexLineFollowerCamera_tests)


include_directories(${RobotexLineFollowerCamera_src_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include)
add_subdirectory(lib/gtest-1.7.0)
#add_subdirectory(fake)


add_executable(runTests
        src/exampletest.cpp
        src/exampletest2.cpp
        )

target_link_libraries(runTests gtest_main)
#target_link_libraries(runTests LiveOV7670_camera)
#target_link_libraries(runTests fakeArduino)



