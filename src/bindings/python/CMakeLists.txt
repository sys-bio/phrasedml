###############################################################################
#
# Description  : CMake build script for phrasedml Python bindings
# Author(s)    : Lucian Smith, from libsbml and Frank Bergmann
#
###############################################################################

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
include(FindPythonLibs)
include(FindPythonInterp)


####################################################################
#
# determine local dependencies, so as to re-swig if one of them changed
# 

file(GLOB SWIG_DEPENDENCIES 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.i 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../swig/*.i
        ${CMAKE_CURRENT_SOURCE_DIR}/../swig/*.h
        )


#
# Remove SWIG wrappers if requested
#
if (PHRASEDML_REMOVE_WRAPPERS)
  foreach(file 
    ${CMAKE_CURRENT_BINARY_DIR}/phrasedml_wrap.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/pydoc-normal.i
    ${CMAKE_CURRENT_BINARY_DIR}/pydoc-doxygen.i
  )
  if (EXISTS ${file})
      FILE(REMOVE ${file})
  endif()
  endforeach()
endif(PHRASEDML_REMOVE_WRAPPERS)

ADD_CUSTOM_COMMAND(        
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/phrasedml_wrap.cpp
    COMMAND "${PYTHON_EXECUTABLE}"
    ARGS    "${CMAKE_CURRENT_SOURCE_DIR}/../swig/swigdoc.py"
            python
            -I"${CMAKE_CURRENT_SOURCE_DIR}/../.."
            -D"${CMAKE_CURRENT_SOURCE_DIR}/../../../doc"
            "${CMAKE_CURRENT_SOURCE_DIR}/../swig/phrasedml.i"
            "${CMAKE_CURRENT_BINARY_DIR}/pydoc-doxygen.i"
    COMMAND "${PYTHON_EXECUTABLE}"
    ARGS    "${CMAKE_CURRENT_SOURCE_DIR}/doc-converter/rewrite_pydoc.py"
            -f "${CMAKE_CURRENT_BINARY_DIR}/pydoc-doxygen.i"
            -o "${CMAKE_CURRENT_BINARY_DIR}/pydoc-normal.i"
    COMMAND "${CMAKE_COMMAND}"
    ARGS    -E rename pydoc-doxygen.i pydoc.i
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS    -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
            -I${CMAKE_CURRENT_SOURCE_DIR} 
            -I${CMAKE_CURRENT_BINARY_DIR} 
            -I${CMAKE_SOURCE_DIR}/src
            -I${CMAKE_SOURCE_DIR}/include
            -c++
            -python        
            ${SWIG_EXTRA_ARGS}         
            -o ${CMAKE_CURRENT_BINARY_DIR}/phrasedml_wrap.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/phrasedml.i
    COMMAND "${CMAKE_COMMAND}"
    ARGS    -E rename pydoc.i pydoc-doxygen.i
    COMMAND "${CMAKE_COMMAND}"
    ARGS    -E rename libphrasedml.py phrasedml-doxygen.py
    COMMAND "${CMAKE_COMMAND}"
    ARGS    -E rename pydoc-normal.i pydoc.i
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS    -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
            -I${CMAKE_CURRENT_SOURCE_DIR} 
            -I${CMAKE_CURRENT_BINARY_DIR} 
            -I${CMAKE_SOURCE_DIR}/src
            -I${CMAKE_SOURCE_DIR}/include
            -c++
            -python        
            ${SWIG_EXTRA_ARGS}         
            -o ${CMAKE_CURRENT_BINARY_DIR}/phrasedml_wrap.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/phrasedml.i
    COMMAND "${CMAKE_COMMAND}"
    ARGS    -E rename pydoc.i pydoc-normal.i 
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/phrasedml.i
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/doc-converter/rewrite_pydoc.py
            ${CMAKE_CURRENT_SOURCE_DIR}/../swig/swigdoc.py
            ${SWIG_DEPENDENCIES}
    COMMENT "Swig Python source") 

add_custom_target(binding_python_swig ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/phrasedml_wrap.cpp)

####################################################################
#
# Build native library
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../swig)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${PYTHON_INCLUDE_DIRS})
if (EXTRA_INCLUDE_DIRS) 
 include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

if (MSVC)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC)

add_library(binding_python_lib SHARED phrasedml_wrap.cpp)
add_dependencies( binding_python_lib binding_python_swig) 

set_target_properties (binding_python_lib PROPERTIES OUTPUT_NAME "_libphrasedml")
if (UNIX)
        set_target_properties (binding_python_lib PROPERTIES PREFIX "")
        set_target_properties (binding_python_lib PROPERTIES SUFFIX ".so")
else()                
        if (CYGWIN)
                set_target_properties (binding_python_lib PROPERTIES PREFIX "")
                set_target_properties (binding_python_lib PROPERTIES SUFFIX ".dll")
        else()
                set_target_properties (binding_python_lib PROPERTIES SUFFIX ".pyd")        
        endif()
endif()

#message(STATUS "libraries: ${LIBPHRASEDML_LIBS}\nphrasedml:${LIBPHRASEDML_LIBRARY}")

target_link_libraries(binding_python_lib ${LIBPHRASEDML_LIBS} ${LIBPHRASEDML_LIBRARY}-static ${PYTHON_LIBRARIES})

if(APPLE)
  set_target_properties(binding_python_lib PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
endif()

# 
# Determine the python installation directory
#
set(PYTHON_PACKAGE_INSTALL_DIR)
if (UNIX OR CYGWIN) 
  execute_process(COMMAND "${PYTHON_EXECUTABLE}" -c "import sys;import platform; sys.stdout.write(platform.python_version()[:3])"
    OUTPUT_VARIABLE PYTHON_VERSION)
  set(PYTHON_PACKAGE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/python${PYTHON_VERSION}/site-packages)
else()
  set(PYTHON_PACKAGE_INSTALL_DIR ${MISC_PREFIX}bindings/python)
endif()

INSTALL(TARGETS binding_python_lib DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/phrasedml )

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/libphrasedml.pth" "phrasedml\n")
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libphrasedml.pth  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libphrasedml.py  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/phrasedml )

if (NOT UNIX)
  file(GLOB new_win_dependencies "${CMAKE_SOURCE_DIR}/win32/*.dll")
  install(FILES ${new_win_dependencies} DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/phrasedml )
endif()

#Install the __init.py__ file
install(FILES ${CMAKE_SOURCE_DIR}/src/bindings/python/__init__.py DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/phrasedml )

####################################################################
#
# testing
#

#if(WITH_CHECK)

        # copy test files to build dir
#        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

        # run python tests
#        add_test(NAME test_python_binding 
#                 COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/test.py
#                 -p $<TARGET_FILE_DIR:binding_python_lib> -b ${CMAKE_CURRENT_SOURCE_DIR}/test)

#endif()