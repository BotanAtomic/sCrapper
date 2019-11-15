cmake_minimum_required(VERSION 3.14)
project(sCrapper C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-pthread -lm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CURL_LIBRARY "-lcurl")
set(CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
find_package(CURL REQUIRED)

message(${CURL_LIBRARIES})

include_directories(${CURL_INCLUDE_DIRS})
link_directories(${CURL_LIBRARIES})

include_directories(include)

add_executable(sCrapper src/core/main.c src/configuration/configuration.c include/configuration.h src/shell/shell.c include/shell.h src/scanner/scanner.c
        include/scanner.h include/list.h src/list/list.c src/configuration/parser.c include/parser.h src/utils/utils.c include/utils.h src/scheduler/scheduler.c
        include/scheduler.h src/comparator/comparaor.c include/comparator.h src/scrapper/scrapper.c include/scrapper.h src/analyser/analyser.c include/analyser.h)

target_link_libraries(sCrapper curl)
