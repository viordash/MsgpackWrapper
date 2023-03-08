project(MsgpackWrapperTests)


include(CTest)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -Wno-write-strings -Wno-overflow -Wno-conversion-null")
endif()

if(WIN32)
  add_definitions("/wd4251")
  add_definitions("/wd4305")
  add_definitions("/wd4309")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

add_subdirectory(cpputest)

set(CPPUTEST_SOURCE_DIRS 
	cpputest/include 
	cpputest/src 
	cpputest/CppUTest 		
	)
	
set(CPPUTEST_SOURCE_FILES 	
		${CMAKE_CURRENT_SOURCE_DIR}/../src/MsgpackValueBase.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/MsgpackValue.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/MsgpackObject.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/MsgpackArrayBase.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/MsgpackArray.cpp	
		${CMAKE_CURRENT_SOURCE_DIR}/../src/MsgpackObjectsArray.cpp
	)

add_executable(MsgpackStringValueTestsGroup     
	${CPPUTEST_SOURCE_FILES}
    MsgpackStringValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(MsgpackStringValueTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(MsgpackStringValueTestsGroup CppUTest)
target_link_libraries(MsgpackStringValueTestsGroup msgpack-c)
target_include_directories(MsgpackStringValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(MsgpackStringValueTestsGroup MsgpackStringValueTestsGroup)

add_executable(MsgpackDataValueTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    MsgpackDataValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(MsgpackDataValueTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(MsgpackDataValueTestsGroup CppUTest)
target_link_libraries(MsgpackDataValueTestsGroup msgpack-c)
target_include_directories(MsgpackDataValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(MsgpackDataValueTestsGroup MsgpackDataValueTestsGroup)

add_executable(MsgpackNumericValueTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    MsgpackNumericValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(MsgpackNumericValueTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(MsgpackNumericValueTestsGroup CppUTest)
target_link_libraries(MsgpackNumericValueTestsGroup msgpack-c)
target_include_directories(MsgpackNumericValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(MsgpackNumericValueTestsGroup MsgpackNumericValueTestsGroup)

add_executable(MsgpackObjectTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    MsgpackObjectTestsGroup.cpp)
if(WIN32)
	target_link_libraries(MsgpackObjectTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(MsgpackObjectTestsGroup CppUTest)
target_link_libraries(MsgpackObjectTestsGroup msgpack-c)
target_include_directories(MsgpackObjectTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(MsgpackObjectTestsGroup MsgpackObjectTestsGroup)

add_executable(MsgpackArrayTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    MsgpackArrayTestsGroup.cpp)
if(WIN32)
	target_link_libraries(MsgpackArrayTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(MsgpackArrayTestsGroup CppUTest)
target_link_libraries(MsgpackArrayTestsGroup msgpack-c)
target_include_directories(MsgpackArrayTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(MsgpackArrayTestsGroup MsgpackArrayTestsGroup)

add_executable(MsgpackHeavyDutyTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    MsgpackHeavyDutyTestsGroup.cpp)
if(WIN32)
	target_link_libraries(MsgpackHeavyDutyTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(MsgpackHeavyDutyTestsGroup CppUTest)
target_link_libraries(MsgpackHeavyDutyTestsGroup msgpack-c)
target_include_directories(MsgpackHeavyDutyTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(MsgpackHeavyDutyTestsGroup MsgpackHeavyDutyTestsGroup)