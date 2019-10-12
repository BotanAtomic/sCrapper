cmake_minimum_required(VERSION 3.14)
project(sCrapper C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(sCrapper src/core/main.c src/configuration/configuration.c include/configuration.h src/shell/shell.c include/shell.h src/scanner/scanner.c include/scanner.h include/list.h src/list/list.c)