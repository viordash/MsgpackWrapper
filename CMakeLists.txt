cmake_minimum_required(VERSION 3.8.0)
project(MsgpackWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

set(MSGPACK_BUILD_TESTS OFF CACHE BOOL "Disable tests")
set(MSGPACK_GEN_COVERAGE OFF CACHE BOOL "Disable coverage")
set(MSGPACK_BUILD_EXAMPLES OFF CACHE BOOL "Disable examples")
set(MSGPACK_ENABLE_SHARED OFF CACHE BOOL "Disable shared")
set(MSGPACK_ENABLE_STATIC ON CACHE BOOL "Enable static")

add_subdirectory(msgpack-c)
get_target_property(MSGPACK_BINARY_INCLUDE_DIRS msgpack-c BINARY_DIR)

include_directories(
    include
    msgpack-c/include
    msgpack-c/include/msgpack
    ${MSGPACK_BINARY_INCLUDE_DIRS}/include
    ${MSGPACK_BINARY_INCLUDE_DIRS}/include/msgpack
)

if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

set(CPP_SOURCE_FILES 
  src/MsgpackValueBase.cpp
  src/MsgpackValue.cpp
  src/MsgpackObject.cpp
  src/MsgpackArrayBase.cpp
  src/MsgpackArray.cpp
  src/MsgpackObjectsArray.cpp
)

add_library(MsgpackWrapper STATIC ${CPP_SOURCE_FILES})

target_link_libraries(MsgpackWrapper PUBLIC msgpack-c)

target_include_directories(MsgpackWrapper PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/msgpack-c/include
    ${CMAKE_CURRENT_SOURCE_DIR}/msgpack-c/include/msgpack
    ${MSGPACK_BINARY_INCLUDE_DIRS}/include
    ${MSGPACK_BINARY_INCLUDE_DIRS}/include/msgpack
)

if(PROJECT_IS_TOP_LEVEL AND NOT MSGPACKWRAPPER_SKIP_TESTING)
    enable_testing() 
    add_subdirectory(Tests)
endif()