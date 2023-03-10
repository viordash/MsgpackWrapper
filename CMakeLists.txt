cmake_minimum_required(VERSION 3.8.0)
project(MsgpackWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)


include_directories(include)

if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)


set (MSGPACK_BUILD_TESTS  OFF)
set (MSGPACK_GEN_COVERAGE  OFF)
set (MSGPACK_BUILD_EXAMPLES  OFF)
set (MSGPACK_ENABLE_SHARED OFF)
set (MSGPACK_ENABLE_STATIC  ON)

include_directories(msgpack-c/include/msgpack msgpack-c/include msgpack-c/src)
include_directories(build/msgpack-c/include build/msgpack-c/include/msgpack)
add_subdirectory(msgpack-c)

set(CPP_SOURCE_FILES 
src/MsgpackValueBase.cpp
src/MsgpackValue.cpp
src/MsgpackObject.cpp
src/MsgpackArrayBase.cpp
src/MsgpackArray.cpp
src/MsgpackObjectsArray.cpp
)

add_executable(MsgpackWrapper     
    main.cpp 
	${CPP_SOURCE_FILES}
    )

target_link_libraries(MsgpackWrapper msgpack-c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


enable_testing()
add_subdirectory(Tests)