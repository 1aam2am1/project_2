cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors")

project(project_2)
add_executable(${PROJECT_NAME})

# check git branch name
find_package(Git)
execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE GIT_BRANCH
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# set EXECUTABLE_NAME
if (${GIT_BRANCH} MATCHES "master")
    set(EXECUTABLE_NAME "Smart_Control")
else ()
    set(EXECUTABLE_NAME "Smart_Control-${GIT_BRANCH}")
endif ()


# Define sources and executable
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE GENERATED_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE GENERATED_HEADERS ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/src/*.h)


target_sources(${PROJECT_NAME} PRIVATE main.cpp ${GENERATED_SOURCES} ${GENERATED_HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}")