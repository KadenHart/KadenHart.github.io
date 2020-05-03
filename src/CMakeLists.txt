cmake_minimum_required(VERSION 3.15)
project(math4610)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(math4610 SHARED library.cpp library.hpp)
set_target_properties(math4610 PROPERTIES LINKER_LANGUAGE CXX)

add_executable(TS1_Demo main.cpp)
target_link_libraries(TS1_Demo ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/libmath4610.dll)

add_executable(TS2_Demo TS2Demo.cpp)
target_link_libraries(TS2_Demo ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/libmath4610.dll)

add_executable(TS3_Demo TS3Demo.cpp)
target_link_libraries(TS3_Demo ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/libmath4610.dll)

add_executable(TS4_Demo TS4Demo.cpp)
target_link_libraries(TS4_Demo ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/libmath4610.dll)

add_executable(TS5_Demo TS5Demo.cpp)
target_link_libraries(TS5_Demo ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/libmath4610.dll)

add_executable(TS6_Demo TS6Demo.cpp)
target_link_libraries(TS6_Demo ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/libmath4610.dll)