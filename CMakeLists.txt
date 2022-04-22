cmake_minimum_required(VERSION 3.20)

project(random LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set(WFLAGS -Wall -Wextra -pedantic)
set(OFLAGS -O2 -flto)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -DNDEBUG ${WFLAGS} ${OFLAGS})

find_package(benchmark REQUIRED)
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)