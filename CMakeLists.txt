cmake_minimum_required(VERSION 3.10)

project(CE)

include_directories(include)
include_directories(src)

file(GLOB_RECURSE SRC "src/ce/graph/*.h"
                      "src/ce/graph/*.cc")
                    #   "src/ce/common/.h"
                    #   "src/ce/common/.cc")

add_library(ce SHARED ${SRC})