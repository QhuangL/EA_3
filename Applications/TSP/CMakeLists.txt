cmake_minimum_required(VERSION 3.0.0)
project(TSP VERSION 0.1.0)




# set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp src/TSP.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

message(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_LIBS})

target_link_libraries(${PROJECT_NAME} 
    Dao
    ${OpenCV_LIBS}
)