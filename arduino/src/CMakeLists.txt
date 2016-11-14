cmake_minimum_required(VERSION 3.2)
project(RobotexLineFollowerCamera_src)



add_library(LiveOV7670_line
        line/Line.cpp
        line/RowLinePosition.cpp
        )


