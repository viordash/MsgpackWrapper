cmake_minimum_required(VERSION 3.8.0)
project(MsgpackWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)

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

if(PROJECT_IS_TOP_LEVEL)
    add_executable(MsgpackWrapper main.cpp ${CPP_SOURCE_FILES})    
    target_link_libraries(MsgpackWrapper PRIVATE msgpack-c)

    IF (NOT MSGPACKWRAPPER_SKIP_TESTING)
        enable_testing()
        add_subdirectory(Tests)
    ENDIF ()
ELSE ()
    ADD_LIBRARY(MsgpackWrapper main.cpp ${CPP_SOURCE_FILES})    
    target_link_libraries(MsgpackWrapper PRIVATE msgpack-c)

ENDIF ()

OPTION (MSGPACK_BUILD_TESTS  OFF)
OPTION (MSGPACK_GEN_COVERAGE  OFF)
OPTION (MSGPACK_BUILD_EXAMPLES  OFF)
SET (MSGPACK_ENABLE_SHARED OFF)
SET (MSGPACK_ENABLE_STATIC  ON)

target_include_directories(MsgpackWrapper PRIVATE msgpack-c/include/msgpack msgpack-c/include msgpack-c/src)
add_subdirectory(msgpack-c)