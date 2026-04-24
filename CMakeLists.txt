cmake_minimum_required(VERSION 3.16)

project(evalground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(eval
    src/main.cpp
    src/avaliacao.cpp
    src/prompt_parser.cpp
)

target_include_directories(eval PRIVATE src)

enable_testing()
