cmake_minimum_required(VERSION 3.17)
project(myOwn C)

set(CMAKE_C_STANDARD 99)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(myOwn main.c utilsAndConverters.c operatorsTranslations.c fileIO.c memory.c registers.c)