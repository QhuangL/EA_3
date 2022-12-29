project(Dao)

file(GLOB_RECURSE CPPFILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)


add_library(${PROJECT_NAME} "${CPPFILES}")
add_library(sub::Dao ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/Evolution
    ${PROJECT_SOURCE_DIR}/include/Math
    ${PROJECT_SOURCE_DIR}/include/Utils
    
)