###############################################################################
#
# Description  : CMake build script for phrasedml Python bindings
# Author(s)    : Lucian Smith, from libsbml and Frank Bergmann
#
###############################################################################

find_package(PythonInterp)
# specify that the same python library should be found
# as the one the selected interpreter uses
set (Python_ADDITIONAL_VERSIONS ${PYTHON_VERSION_STRING})

SET(LIBPHRASEDML_VERSION_STRING_NO_V "${LIBPHRASEDML_VERSION_MAJOR}.${LIBPHRASEDML_VERSION_MINOR}${LIBPHRASEDML_VERSION_PATCH}${LIBPHRASEDML_VERSION_RELEASE}")

SET(PYTHON_CTYPES_FILE "${CMAKE_CURRENT_BINARY_DIR}/phrasedml.py")

#Create the 'phrasedml.py' ctypes-based library from 'createPhrasedmlLib.py'.
ADD_CUSTOM_COMMAND(
    OUTPUT   ${PYTHON_CTYPES_FILE}
    COMMAND "${PYTHON_EXECUTABLE}"
    ARGS    "${CMAKE_SOURCE_DIR}/src/bindings/python/createPhrasedmlLib.py" "${CMAKE_SOURCE_DIR}/src/"
    COMMENT "Convert header file to ctypes Python bindings.")

ADD_CUSTOM_TARGET(python_ctypes_lib ALL DEPENDS ${PYTHON_CTYPES_FILE})

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/phrasedml.py PROPERTIES GENERATED TRUE)

#Create files from .in files
set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
set(INIT_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py.in")
set(INIT_PY    "${CMAKE_CURRENT_BINARY_DIR}/__init__.py")

configure_file(${SETUP_PY_IN} ${SETUP_PY})
configure_file(${INIT_PY_IN} ${INIT_PY})


#All the files that need to be installed in the python library directory.
file (GLOB phrasedml_python_files
    ${INIT_PY}
    ${CMAKE_CURRENT_BINARY_DIR}/phrasedml.py
    ${CMAKE_CURRENT_BINARY_DIR}/libphrasedml.pth
    ${CPACK_PACKAGE_DESCRIPTION_FILE}
    ${CPACK_RESOURCE_FILE_LICENSE}
    ${win_dependencies}
)


if (PYTHON_SYSTEM_INSTALL)
   #Copy all the files into a local 'phrasedml' directory.
   INSTALL(FILES ${phrasedml_python_files} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/phrasedml)
#   install(TARGETS ${LIBPHRASEDML_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/phrasedml)

   #Now run 'python setup.py install' with that directory as the target.
   INSTALL(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E chdir ${CMAKE_CURRENT_BINARY_DIR} ${PYTHON_EXECUTABLE} ${SETUP_PY} install)")
endif()

#...and/or we instead copy phrasedml_python_files into the install directory, along with setup.py, and let the user run that directly.

set(PYTHON_PACKAGE_INSTALL_DIR "bindings/python")
if (PYTHON_LOCAL_INSTALL)

   INSTALL(FILES ${phrasedml_python_files}  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/phrasedml)
   INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/phrasedml.py DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/phrasedml)
#   install(TARGETS ${LIBPHRASEDML_LIBRARY}  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/phrasedml)
   INSTALL(FILES ${SETUP_PY}  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR})
   INSTALL(TARGETS ${LIBPHRASEDML_LIBRARY}  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/phrasedml)

endif()

if (NOT PYTHON_SYSTEM_INSTALL)
   if (NOT PYTHON_LOCAL_INSTALL)
        message(WARNING "   Python bindings will be created, but not installed.  Install them by hand from ${CMAKE_CURRENT_BINARY_DIR},\n   or turn on PYTHON_SYSTEM_INSTALL and/or PYTHON_LOCAL_INSTALL.")
   endif()
endif()

