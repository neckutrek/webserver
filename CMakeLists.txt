cmake_minimum_required(VERSION 3.1)

project(myproject)

set(CMAKE_EXECUTABLE_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_LINK_LIBRARIES "")

find_package(Boost)
if(Boost_FOUND)
   set(PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
   set(PROJECT_LINK_LIBRARIES ${PROJECT_LINK_LIBRARIES} ${Boost_LIBRARIES})
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if (Threads_FOUND)
   set(PROJECT_LINK_LIBRARIES ${PROJECT_LINK_LIBRARIES} Threads::Threads)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wextra -Wpedantic -Wall -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

add_subdirectory("${PROJECT_SOURCE_DIR}/src")
