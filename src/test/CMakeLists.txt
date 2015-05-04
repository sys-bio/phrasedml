####################################################################
#
# CMake Build Script for libphrasedml tests
#
# 
include(${CMAKE_SOURCE_DIR}/common.cmake)

file(GLOB C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

foreach(c_file ${C_FILES})
	set_source_files_properties(${c_file} PROPERTIES LANGUAGE CXX)
endforeach()

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h )

set(TEST_FILES ${CPP_FILES} ${C_FILES} ${H_FILES})

include_directories(BEFORE ${CMAKE_SOURCE_DIR}/src)
if (EXTRA_INCLUDE_DIRS) 
 include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

include_directories(${LIBCHECK_INCLUDE_DIR})
add_executable(test_phrasedml ${TEST_FILES})
target_link_libraries(test_phrasedml ${LIBPHRASEDML_LIBRARY}-static ${LIBPHRASEDML_LIBS} ${LIBCHECK_LIBRARY} )
add_test(test_phrasedml_run ${CMAKE_CURRENT_BINARY_DIR}/test_phrasedml )
set_tests_properties(test_phrasedml_run PROPERTIES ENVIRONMENT 
	"srcdir=${CMAKE_CURRENT_SOURCE_DIR}")
