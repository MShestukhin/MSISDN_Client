project(MNP_Client C CXX)
#SET(CMAKE_CXX_FLAGS "-std=c++0x")
SET(CMAKE_CXX_FLAGS "-lrt -lpthread")
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system log thread filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_library(libconfig STATIC IMPORTED)
set_target_properties(libconfig PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libconfig++.a)

add_library(libclntsh SHARED IMPORTED)
set_target_properties(libclntsh PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libclntsh.so.11.1)

add_library(libocilib STATIC IMPORTED)
set_target_properties(libocilib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libocilib.a)

target_link_libraries(MNP_Client libocilib)
target_link_libraries(MNP_Client libclntsh)
target_link_libraries(MNP_Client ${Boost_LIBRARIES})
target_link_libraries(MNP_Client libconfig)
