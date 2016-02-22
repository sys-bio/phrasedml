## @file    CMakeLists.txt
## @brief   CMake build script for standalone programs
## @author  Lucian Smith
##

# only compile examples if specified, but always copy samples
if(WITH_EXAMPLES)
   include_directories("${CMAKE_SOURCE_DIR}/${PHRASEDML_SRC_DIR}")

   add_subdirectory(converter)

endif(WITH_EXAMPLES)
