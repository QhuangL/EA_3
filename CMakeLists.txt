cmake_minimum_required(VERSION 3.0.0)
project(Dao VERSION 0.1.0)



file(GLOB_RECURSE CPPFILES
    src/*.cpp
    Application/*.cpp
)

add_executable(Dao main.cpp "${CPPFILES}")

target_include_directories(Dao PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}"
)


