cmake_minimum_required(VERSION 3.0.0)
project(DAO VERSION 0.1.0)

file(GLOB_RECURSE CPPFILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)


add_library(${PROJECT_NAME} "${CPPFILES}")
add_library(Dao ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)