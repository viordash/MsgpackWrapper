cmake_minimum_required(VERSION 3.8.0)
project(MsgpackWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

set(MSGPACK_BUILD_TESTS OFF CACHE BOOL "Disable tests")
set(MSGPACK_GEN_COVERAGE OFF CACHE BOOL "Disable coverage")
set(MSGPACK_BUILD_EXAMPLES OFF CACHE BOOL "Disable examples")
set(MSGPACK_ENABLE_SHARED OFF CACHE BOOL "Disable shared")
set(MSGPACK_ENABLE_STATIC ON CACHE BOOL "Enable static")

option(MSGPACKWRAPPER_BUILD_DEMO "Build demonstration application" ON)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -fno-rtti")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -fno-rtti")
    elseif(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL /MP")
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -DNDEBUG")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -Os -DNDEBUG")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wconversion -Wsign-conversion")
endif()

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    if(MSVC)
        add_compile_options(/W4 /WX)
    endif()
endif()

add_subdirectory(msgpack-c)

get_target_property(MSGPACK_BINARY_INCLUDE_DIRS msgpack-c BINARY_DIR)

include_directories(
    include
    msgpack-c/include
    msgpack-c/include/msgpack
    ${MSGPACK_BINARY_INCLUDE_DIRS}/include
    ${MSGPACK_BINARY_INCLUDE_DIRS}/include/msgpack
)

set(CPP_SOURCE_FILES 
  src/MsgpackValueBase.cpp
  src/MsgpackValue.cpp
  src/MsgpackObject.cpp
  src/MsgpackArrayBase.cpp
  src/MsgpackArray.cpp
  src/MsgpackObjectsArray.cpp
)

add_library(MsgpackWrapper STATIC ${CPP_SOURCE_FILES})

target_link_libraries(MsgpackWrapper PRIVATE msgpack-c)

target_include_directories(MsgpackWrapper PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/msgpack-c/include
    ${CMAKE_CURRENT_SOURCE_DIR}/msgpack-c/include/msgpack
    ${MSGPACK_BINARY_INCLUDE_DIRS}/include
    ${MSGPACK_BINARY_INCLUDE_DIRS}/include/msgpack
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set_target_properties(MsgpackWrapper PROPERTIES 
            INTERPROCEDURAL_OPTIMIZATION TRUE
            LINK_FLAGS "-flto"
        )
    elseif(MSVC)
        set_target_properties(MsgpackWrapper PROPERTIES 
            INTERPROCEDURAL_OPTIMIZATION TRUE
            LINK_FLAGS "/LTCG"
        )
    endif()
endif()

if(MSGPACKWRAPPER_BUILD_DEMO)
    add_executable(MsgpackWrapperDemo main.cpp)
    target_link_libraries(MsgpackWrapperDemo MsgpackWrapper)
    target_include_directories(MsgpackWrapperDemo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/msgpack-c/include
        ${CMAKE_CURRENT_SOURCE_DIR}/msgpack-c/include/msgpack
        ${MSGPACK_BINARY_INCLUDE_DIRS}/include
        ${MSGPACK_BINARY_INCLUDE_DIRS}/include/msgpack
    )
endif()

if(PROJECT_IS_TOP_LEVEL AND NOT MSGPACKWRAPPER_SKIP_TESTING)
    enable_testing() 
    add_subdirectory(Tests)
endif()