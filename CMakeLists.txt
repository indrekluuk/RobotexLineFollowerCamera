cmake_minimum_required(VERSION 3.2)
project(RobotexLineFollowerCamera)

include(CMakeListsPrivate.txt)

add_definitions(-DF_CPU=16000000L)
add_definitions(-DARDUINO_ARCH_AVR)
add_definitions(-DARDUINO_AVR_NANO)
add_definitions(-DARDUINO=10608)
add_definitions(-DPLATFORMIO=020806)
add_definitions(-D__AVR_ATmega328P__)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(RobotexLineFollowerCamera
        src/camera/base/CameraOV7670Base.cpp
        src/camera/base/CameraOV7670RegsClock.cpp
        src/camera/base/CameraOV7670RegsDefault.cpp
        src/camera/base/CameraOV7670RegsQQVGA.cpp
        src/camera/base/CameraOV7670RegsRGB565.cpp
        src/camera/base/CameraOV7670RegsYUV422.cpp
        src/screen/Adafruit_ST7735_mod.cpp
        src/camera/CameraOV7670_QQVGA_10hz.cpp
        src/camera/CameraOV7670_QQVGA_10hz.h src/camera/base/BufferedCameraOV7670.h)
