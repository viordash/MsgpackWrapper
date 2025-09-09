project(MsgpackWrapperTests)

include(CTest)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -Wno-write-strings -Wno-overflow -Wno-conversion-null")
endif()

if(WIN32)
    add_definitions("/wd4251")
    add_definitions("/wd4305")
    add_definitions("/wd4309")
    add_definitions("/wd4611")
    add_definitions("/wd4100")
    add_definitions("/wd4127")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

add_subdirectory(cpputest)

set(CPPUTEST_SOURCE_DIRS 
    cpputest/include 
    cpputest/src 
    cpputest/CppUTest         
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/msgpack-c/include
    ${CMAKE_SOURCE_DIR}/msgpack-c/include/msgpack
    ${CMAKE_BINARY_DIR}/msgpack-c/include
    ${CMAKE_BINARY_DIR}/msgpack-c/include/msgpack
)

function(add_msgpack_test test_name test_source)
    add_executable(${test_name} ${test_source})
    
    if(WIN32)
        target_link_libraries(${test_name} Winmm.lib)
    endif(WIN32)
    
    target_link_libraries(${test_name} CppUTest MsgpackWrapper)
    target_include_directories(${test_name} PRIVATE ${CPPUTEST_SOURCE_DIRS})
    add_test(${test_name} ${test_name})
endfunction()

add_msgpack_test(MsgpackStringValueTestsGroup MsgpackStringValueTestsGroup.cpp)
add_msgpack_test(MsgpackDataValueTestsGroup MsgpackDataValueTestsGroup.cpp)
add_msgpack_test(MsgpackNumericValueTestsGroup MsgpackNumericValueTestsGroup.cpp)
add_msgpack_test(MsgpackObjectTestsGroup MsgpackObjectTestsGroup.cpp)
add_msgpack_test(MsgpackArrayTestsGroup MsgpackArrayTestsGroup.cpp)
add_msgpack_test(MsgpackHeavyDutyTestsGroup MsgpackHeavyDutyTestsGroup.cpp)