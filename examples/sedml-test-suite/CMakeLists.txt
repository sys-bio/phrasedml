## @file    CMakeLists.txt
## @brief   CMake build script
## @author  Lucian Smith

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/create-test-suite.cpp )
file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h )

set(TEST_FILES ${CPP_FILES} ${H_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(BEFORE ${LIBSBML_ROOT_SOURCE_DIR}/src)
include_directories(BEFORE ${LIBSBML_ROOT_BINARY_DIR}/src)

if (EXTRA_INCLUDE_DIRS) 
 include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

add_executable(create-test-suite ${TEST_FILES})
target_link_libraries(create-test-suite ${LIBSBML_LIBRARY}-static)

install(TARGETS create-test-suite DESTINATION bin)
