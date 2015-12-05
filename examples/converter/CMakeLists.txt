## @file    CMakeLists.txt
## @brief   CMake build script
## @author  Lucian Smith

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/phrasedml-convert.cpp )
file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h )

set(TEST_FILES ${CPP_FILES} ${H_FILES})

add_executable(phrasedml-convert ${TEST_FILES})
target_link_libraries(phrasedml-convert ${LIBPHRASEDML_LIBRARY}-static ${LIBPHRASEDML_LIBS})

install(TARGETS phrasedml-convert DESTINATION bin)
