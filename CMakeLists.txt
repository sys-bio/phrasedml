####################################################################
#
# CMake Build Script for libphrasedml
#

cmake_minimum_required(VERSION 2.8)
project(libphrasedml)

####################################################################
#
# Set up version information.
#
SET(LIBPHRASEDML_VERSION_MAJOR 1)
SET(LIBPHRASEDML_VERSION_MINOR 3)
SET(LIBPHRASEDML_VERSION_PATCH ".0")
SET(LIBPHRASEDML_VERSION_RELEASE "")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()


####################################################################
#
# the next lines configure the parameters for packaging the binaries
# they can be invoked with: make package / nmake package or by using
# cpack -G zip|deb|rpm|dmg|nsis
#

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An API library for reading, writing, manipulating, and translating PhraSED-ML models")
SET(CPACK_PACKAGE_NAME "libPhraSEDML")
SET(CPACK_PACKAGE_VENDOR "Lucian Smith")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "${LIBPHRASEDML_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${LIBPHRASEDML_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${LIBPHRASEDML_VERSION_PATCH}")
SET(CPACK_PACKAGE_VERSION_RELEASE "${LIBPHRASEDML_VERSION_RELEASE}")
INCLUDE(CPack)

####################################################################
#
# Here we have the main configuration options for libphrasedml
#
option(BUILD_SHARED_LIBS  "Build shared library (Set to OFF to build static libraries)" ON)
option(WITH_SWIG   "Regenerate SWIG-based language bindings." ON )
option(WITH_PYTHON       "Generate Python language bindings." OFF)
option(WITH_EXAMPLES     "Generate example programs, including translator." ON)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS are used), Debug, Release, RelWithDebInfo, MinSizeRel" )
if (WITH_PYTHON)
  option(PYTHON_SYSTEM_INSTALL  "Install the python bindings using setup.py and distutils.  May require admin privileges."    ON )
  option(PYTHON_LOCAL_INSTALL   "Install the python bindings in ${CMAKE_INSTALL_PREFIX}/bindings/python/.  Will probably require the use of PYTHONPATH."    OFF )
  option(WITH_CONDA_BUILDER     "Install files required to build Anaconda packages"  OFF)
  option(WITH_PYTHON_EXAMPLES   "Install Python example files"  OFF)
endif()

# which language bindings should be build
option(WITH_STATIC_NUML     "Use the static version of the libnuml library"      ON )
option(WITH_STATIC_SEDML    "Use the static version of the libsedml library"     ON )
option(WITH_STATIC_SBML     "Use the static version of the libsbml library"      ON )
OPTION(WITH_LIBSBML_EXPAT  "Set if libsbml was compiled with a separate expat library."  ON)
OPTION(WITH_LIBSBML_LIBXML "Set if libsbml was compiled with a separate libxml library." OFF)
OPTION(WITH_LIBSBML_XERCES "Set if libsbml was compiled with a separate xerces library." OFF)
OPTION(WITH_LIBSBML_COMPRESSION "Set if libsbml was compiled with separate zdll and bzip libraries." OFF)
OPTION(PHRASEDML_ENABLE_XPATH_EVAL "Use libxml2 for xpath evaluation." OFF)

set(EXTRA_LIBS "" CACHE STRING "Libraries the other libraries depend on that are in non-standard locations" )

# any of these directories are accepted as default directories.
# this supports multi platform builds on a single system
set(PHRASEDML_DEPENDENCIES_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/dependencies"
        CACHE PATH "Path to dependency package"
        )



# Enable the generation of unit tests. If enabled, all test runners
# will be created and can be run with "make test" or ctest.
# This won't work in Visual Studio 2003, so we disable this option there.
#
if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio 6" AND NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio 7")
    option(WITH_CHECK    "Compile unit tests. Run with 'make test' or 'ctest'." OFF)
endif()


SET(LIBPHRASEDML_VERSION_STRING "v${LIBPHRASEDML_VERSION_MAJOR}.${LIBPHRASEDML_VERSION_MINOR}${LIBPHRASEDML_VERSION_PATCH}${LIBPHRASEDML_VERSION_RELEASE}")
add_definitions( -DLIBPHRASEDML_VERSION_STRING="${LIBPHRASEDML_VERSION_STRING}" )

if (PHRASEDML_ENABLE_XPATH_EVAL)
  find_package(LibXml2 REQUIRED)
  INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
  add_definitions(-DPHRASEDML_ENABLE_XPATH_EVAL)
endif()

####################################################
#   Dependencies

set(DEPENDENCY_INCLUDE_DIR "${PHRASEDML_DEPENDENCIES_INSTALL_PREFIX}/include")

if (NOT EXISTS ${DEPENDENCY_INCLUDE_DIR})
    message(FATAL_ERROR "Cannot find the dependency include directory in your \
dependency install tree. Please ensure the path you have given to -DPHRASEDML_DEPENDENCIES_INSTALL_PREFIX \
exists and is the full path to the installed dependency tree.")
endif ()

set(RR_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(DEPENDENCY_CMAKE_CONFIG_PATHS
        "${PHRASEDML_DEPENDENCIES_INSTALL_PREFIX}/lib/cmake"
        "${PHRASEDML_DEPENDENCIES_INSTALL_PREFIX}/lib64/cmake"
        "${PHRASEDML_DEPENDENCIES_INSTALL_PREFIX}/cmake"
        "${PHRASEDML_DEPENDENCIES_INSTALL_PREFIX}/lib/cmake/Poco"
        )
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${DEPENDENCY_CMAKE_CONFIG_PATHS}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${DEPENDENCY_CMAKE_CONFIG_PATHS}")
message(STATUS "CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")
if (WIN32)
    set(SBML_TARGET_NAME "libsbml-static")
    set(SEDML_TARGET_NAME "libsedml-static")
    set(NUML_TARGET_NAME "libnuml-static")
    set(NUML_TARGET_NAME_NS "libnuml")
    set(SBML_TARGET_NAME_NS "libsbml")
else ()
    set(SBML_TARGET_NAME "sbml-static")
    set(SEDML_TARGET_NAME "sedml-static")
    set(NUML_TARGET_NAME "numl-static")
    set(NUML_TARGET_NAME_NS "numl")
    set(SBML_TARGET_NAME_NS "sbml")
endif (WIN32)


#find_package(Threads) # for libxml2, FindThreads.cmake is shipped with cmake
#find_package(LibLZMA) # for libxml2, LibLZMA.cmake is shipped with cmake
find_package(zlib CONFIG REQUIRED)
#find_package(bzip2 CONFIG REQUIRED)
#find_package(iconv CONFIG REQUIRED)

find_package(expat CONFIG REQUIRED)

## https://stackoverflow.com/questions/32183975/how-to-print-all-the-properties-of-a-target-in-cmake/56738858#56738858
## https://stackoverflow.com/a/56738858/3743145

## Get all properties that cmake supports
execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)
## Convert command output into a CMake list
STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")

list(REMOVE_DUPLICATES CMAKE_PROPERTY_LIST)

function(print_target_properties tgt)
    if(NOT TARGET ${tgt})
      message("There is no target named '${tgt}'")
      return()
    endif()

    foreach (prop ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
        get_target_property(propval ${tgt} ${prop})
        if (propval)
            message ("${tgt} ${prop} = ${propval}")
        endif()
    endforeach(prop)
endfunction(print_target_properties)

cmake_language(CALL print_target_properties zlib::zlibstatic)
cmake_language(CALL print_target_properties expat::expat)

#libsbml now needs to know that we found expat, so we set the relevant flags
set(EXPAT_LIBRARY "expat::expat")
get_target_property(EXPAT_INCLUDE_DIR expat::expat INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(EXPAT_LIBRARY expat::expat LOCATION)
message(STATUS "EXPAT_LIBRARY: ${EXPAT_LIBRARY}")

set(ZLIB_LIBRARY "zlib::zlibstatic")
get_target_property(ZLIB_LIBRARY zlib::zlibstatic LOCATION)
set(ZLIB_INCLUDE_DIR "${PHRASEDML_DEPENDENCIES_INSTALL_PREFIX}/include/")
message(STATUS "ZLIB_LIBRARY: ${ZLIB_LIBRARY}")
message(STATUS "ZLIB_INCLUDE_DIR: ${ZLIB_INCLUDE_DIR}")

#For some reason, something in the bowels of the dependencies needs ZLIB::ZLIB, and won't accept zlib::zlib.
# I stole this from libsbml's CMakeLists.txt file, since they apparently also suffer the same problem
# (and are the probable cause, at that.)  I've only seen this needed on Ubuntu, and even there, it's
# not needed for the azure ubuntu build, just when actually running Ubuntu.
if(NOT TARGET ZLIB::ZLIB)
  add_library(ZLIB::ZLIB UNKNOWN IMPORTED)
  set_target_properties(ZLIB::ZLIB PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    IMPORTED_LOCATION "${ZLIB_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${ZLIB_INCLUDE_DIR}")
endif()

if(NOT TARGET expat)
  add_library(expat UNKNOWN IMPORTED)
  set_target_properties(expat PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    IMPORTED_LOCATION "${EXPAT_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${EXPAT_INCLUDE_DIR}")
endif()


if(NOT TARGET zlibstatic)
  add_library(zlibstatic UNKNOWN IMPORTED)
  set_target_properties(zlibstatic PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    IMPORTED_LOCATION "${ZLIB_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${ZLIB_INCLUDE_DIR}")
endif()

find_package(${SBML_TARGET_NAME} CONFIG REQUIRED)

#Tell libnuml and libsedml not to look for libsbml on their own (since we install the static but not the dynamic versions):
set(VERBOSE ON)
set(FIND_LIBSBML CACHE BOOL "Look for the shared version of libsbml (should be OFF if using libroadrunner-deps" FORCE)
set(FIND_LIBNUML CACHE BOOL "Look for the shared version of libnuml (should be OFF if using libroadrunner-deps" FORCE)


# Now fool sedml into thinking libsbml-static is libsbml.
get_target_property(SBML_INCLUDE_DIR ${SBML_TARGET_NAME} INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SBML_LIBRARY ${SBML_TARGET_NAME} LOCATION)

if(NOT TARGET ${SBML_TARGET_NAME_NS})
  add_library(${SBML_TARGET_NAME_NS} UNKNOWN IMPORTED)
  set_target_properties(${SBML_TARGET_NAME} PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    IMPORTED_LOCATION "${SBML_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${SBML_INCLUDE_DIR}")
endif()

set(LIBSBML_LIBRARY ${SBML_LIBRARY})
set(LIBSBML_INCLUDE_DIR ${SBML_INCLUDE_DIR})

find_package(${NUML_TARGET_NAME} CONFIG REQUIRED)

#Now we need to fool sedml into thinking libnuml-static is libnuml.
get_target_property(NUML_INCLUDE_DIR ${NUML_TARGET_NAME} INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(NUML_LIBRARY ${NUML_TARGET_NAME} LOCATION)

if(NOT TARGET ${NUML_TARGET_NAME_NS})
  add_library(${NUML_TARGET_NAME_NS} UNKNOWN IMPORTED)
  set_target_properties(${NUML_TARGET_NAME} PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    IMPORTED_LOCATION "${NUML_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${NUML_INCLUDE_DIR}")
endif()

find_package(${SEDML_TARGET_NAME} CONFIG REQUIRED)


set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${SBML_TARGET_NAME} )
set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${SEDML_TARGET_NAME} )
set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${NUML_TARGET_NAME} )
set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} expat::expat )
set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} zlib::zlibstatic )

INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${LIBSEDML_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${LIBNUML_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${LIBSBML_INCLUDE_DIR})

if (WITH_COMP_SBML)
    add_definitions( -DUSE_COMP )
endif(WITH_COMP_SBML)



if(WITH_PYTHON)
    message(STATUS "  Using Python                  = ${PYTHON_EXECUTABLE}")
endif()


set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${EXTRA_LIBS} )

###############################################################################
## Enable support for testing ... can be invoked by running ctest
# or make test
#

if(WITH_CHECK)
    # we do use tests, that require 2.8.4
    cmake_minimum_required(VERSION 2.8.4)

    enable_testing()

    find_library(LIBCHECK_LIBRARY
        NAMES check libcheck
        PATHS /usr/lib /usr/local/lib ${LIBSBML_DEPENDENCY_DIR}/lib
        DOC "The file name of the libcheck library."
    )

    find_path(LIBCHECK_INCLUDE_DIR
        NAMES check.h
        PATHS /usr/include /usr/local/include  ${LIBSBML_DEPENDENCY_DIR}/include
        DOC "The directory containing the libcheck include files."
              )

    if(NOT EXISTS "${LIBCHECK_INCLUDE_DIR}/check.h")
        message(FATAL_ERROR "The 'check' include directory appears to be invalid. It should contain the file check.h, but it does not.")
    endif()

    if(${CMAKE_GENERATOR} MATCHES "Visual Studio 6" OR ${CMAKE_GENERATOR} MATCHES "Visual Studio 7")
        message(WARNING "Libcheck is not compatible with Visual Studio 2003 (or earlier versions).")
    endif()


endif(WITH_CHECK)

####################################################################
#
# Need some variables set up, such as the name for the libPhrasedml
# library and the Path and file separator characters
#

if(UNIX)
    set(PATH_SEP "/")
    set(FILE_SEP ":")
    set(LIBPHRASEDML_LIBRARY phrasedml)
else()
    set(PATH_SEP "\\")
    set(FILE_SEP ";")
    set(LIBPHRASEDML_LIBRARY libphrasedml)
endif()


set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Full path to the library output directory")
mark_as_advanced(CMAKE_INSTALL_LIBDIR)



####################################################################
#
# Build the actual libPhrasedml library
#

set (PHRASEDML_SRC_DIR src/)

file(GLOB LIBPHRASEDML_SOURCES
          ${PHRASEDML_SRC_DIR}model.cpp
          ${PHRASEDML_SRC_DIR}modelChange.cpp
          ${PHRASEDML_SRC_DIR}oneStep.cpp
          ${PHRASEDML_SRC_DIR}output.cpp
          ${PHRASEDML_SRC_DIR}phrasedml.tab.cpp
          ${PHRASEDML_SRC_DIR}phrasedml_api.cpp
          ${PHRASEDML_SRC_DIR}registry.cpp
          ${PHRASEDML_SRC_DIR}repeatedTask.cpp
          ${PHRASEDML_SRC_DIR}sbmlx.cpp
          ${PHRASEDML_SRC_DIR}simulation.cpp
          ${PHRASEDML_SRC_DIR}steadyState.cpp
          ${PHRASEDML_SRC_DIR}stringx.cpp
          ${PHRASEDML_SRC_DIR}task.cpp
          ${PHRASEDML_SRC_DIR}uniform.cpp
          ${PHRASEDML_SRC_DIR}variable.cpp
          )

file(GLOB LIBPHRASEDML_HEADERS
          ${PHRASEDML_SRC_DIR}libutil.h
          ${PHRASEDML_SRC_DIR}model.h
          ${PHRASEDML_SRC_DIR}modelChange.h
          ${PHRASEDML_SRC_DIR}oneStep.h
          ${PHRASEDML_SRC_DIR}phrasedml_api.h
          ${PHRASEDML_SRC_DIR}phrasedml-namespace.h
          ${PHRASEDML_SRC_DIR}output.h
          ${PHRASEDML_SRC_DIR}registry.h
          ${PHRASEDML_SRC_DIR}repeatedTask.h
          ${PHRASEDML_SRC_DIR}sbmlx.h
          ${PHRASEDML_SRC_DIR}simulation.h
          ${PHRASEDML_SRC_DIR}steadystate.h
          ${PHRASEDML_SRC_DIR}stringx.h
          ${PHRASEDML_SRC_DIR}task.h
          ${PHRASEDML_SRC_DIR}uniform.h
          ${PHRASEDML_SRC_DIR}variable.h
          )

##### Build the main library #####
add_library(${LIBPHRASEDML_LIBRARY} ${LIBPHRASEDML_HEADERS} ${LIBPHRASEDML_SOURCES})
target_link_libraries(${LIBPHRASEDML_LIBRARY} ${LIBPHRASEDML_LIBS})
#    message(STATUS "  Target link libraries = ${LIBPHRASEDML_LIBS}")
add_definitions(-DLIB_EXPORTS)
install(TARGETS ${LIBPHRASEDML_LIBRARY} DESTINATION lib)
install(FILES   ${LIBPHRASEDML_HEADERS} DESTINATION include)

if (WIN32 AND NOT CYGWIN)
    # don't decorate static library
    set_target_properties(${LIBPHRASEDML_LIBRARY} PROPERTIES COMPILE_DEFINITIONS "LIBLAX_STATIC=1;LIBSEDML_STATIC=1;LIBSBML_STATIC=1")
endif(WIN32 AND NOT CYGWIN)

if (NOT UNIX)
  add_definitions(-DWIN32 -DLIBSBML_EXPORTS -DLIBLAX_EXPORTS)
endif(NOT UNIX)


##### Build the static library #####
add_library (${LIBPHRASEDML_LIBRARY}-static STATIC ${LIBPHRASEDML_HEADERS} ${LIBPHRASEDML_SOURCES})

if (WIN32 AND NOT CYGWIN)
    # don't decorate static library
    set_target_properties(${LIBPHRASEDML_LIBRARY}-static PROPERTIES COMPILE_DEFINITIONS "LIBLAX_STATIC=1;LIBSEDML_STATIC=1;LIBSBML_STATIC=1;LIBPHRASEDML_STATIC=1")
endif(WIN32 AND NOT CYGWIN)

target_link_libraries(${LIBPHRASEDML_LIBRARY}-static ${LIBPHRASEDML_LIBS})

INSTALL(TARGETS ${LIBPHRASEDML_LIBRARY}-static
        DESTINATION lib
  )



####################################################################
#
# Build the bindings.
#

add_subdirectory(src/bindings)


####################################################################
#
# Build the executables.
#

if(WITH_EXAMPLES)
  add_subdirectory(examples)
endif(WITH_EXAMPLES)



####################################################################
#
# Build the test libraries.
#

if(WITH_CHECK)
    message(STATUS "  Using libcheck                = ${LIBCHECK_LIBRARY}")
    add_subdirectory(src/test)
endif()



####################################################################
#
# Build the various command-line executables
#

#add_executable(sbtranslate ${PHRASEDML_SRC_DIR}sbtranslate.cpp)
#add_dependencies(sbtranslate ${LIBPHRASEDML_LIBRARY}-static)
#target_link_libraries(sbtranslate ${LIBPHRASEDML_LIBRARY}-static ${LIBPHRASEDML_LIBS})
#install(TARGETS sbtranslate DESTINATION bin)


####################################################################
#
# Build QT Phrasedml
#

#set (QTPHRASEDML_SRC_DIR QTPhrasedml_src/)
#set (QTPHRASEDML_DIALOG_DIR QTPhrasedml_src/qtfindreplacedialog-1.1/dialogs/)

#file(GLOB QTPHRASEDML_SOURCES
#        ${QTPHRASEDML_SRC_DIR}phrasedmlTab.cpp
#        )

#file(GLOB QTPHRASEDML_HEADERS
#        ${QTPHRASEDML_SRC_DIR}phrasedmlTab.h
#        ${QTPHRASEDML_SRC_DIR}CellMLTab.h
#        )

#file(GLOB QTPHRASEDML_FORMS
#        ${QTPHRASEDML_DIALOG_DIR}findreplacedialog.ui
#        ${QTPHRASEDML_DIALOG_DIR}findreplaceform.ui
#        ${QTPHRASEDML_SRC_DIR}GoToLineDialog.ui
#        ${QTPHRASEDML_SRC_DIR}GoToLineForm.ui
#        )

#file(GLOB QTPHRASEDML_RESOURCE
#        ${QTPHRASEDML_SRC_DIR}phrasedmlicon.rc
#        )

if (WITH_QTPHRASEDML)
        find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED )
        include(${QT_USE_FILE})
        INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${PHRASEDML_SRC_DIR} ${QTPHRASEDML_SRC_DIR} ${QTPHRASEDML_DIALOG_DIR} ${QT_INCLUDES})
        QT4_WRAP_CPP(QTPHRASEDML_MOC_SRCS ${QTPHRASEDML_HEADERS})
        QT4_ADD_RESOURCES(RC_SRC_FILES ${QTPHRASEDML_SRC_DIR}phrasedml.qrc )
        QT4_WRAP_UI(QTPHRASEDML_FORMS_HEADERS ${QTPHRASEDML_FORMS})
        source_group(MOC_sources FILES ${QTPHRASEDML_MOC_SRCS})
        if (WIN32)
           link_libraries(${QT_QTMAIN_LIBRARY})
        endif(WIN32)
        set( MACOSX_BUNDLE_ICON_FILE phrasedml.icns )
        set (QTPHRASEDML_LIBRARIES ${QT_LIBRARIES} ${LIBPHRASEDML_LIBRARY}-static ${LIBPHRASEDML_LIBS} )
        if (WITH_SBW)
           set(SBW_DEFINITIONS "-DSBW_INTEGRATION" )
           find_library(SBW_LIBRARY
        NAMES libsbw.lib sbw.lib libsbw.so libsbw sbw
        PATHS /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
                          ${CMAKE_SOURCE_DIR}/../SBW/install/lib
                          )
           set(QTPHRASEDML_LIBRARIES ${QTPHRASEDML_LIBRARIES} ${SBW_LIBRARY} )

       find_path(SBW_INCLUDE_DIR
        NAMES SBW/config.h
        PATHS /usr/include /usr/local/include
              ${CMAKE_SOURCE_DIR}/include
              ${CMAKE_SOURCE_DIR}/dependencies/include
                          ${CMAKE_SOURCE_DIR}/../SBW/install/include/
              )
           INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${SBW_INCLUDE_DIR})

        endif(WITH_SBW)
        INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
        INCLUDE_DIRECTORIES(${QTPHRASEDML_DIALOG_DIR})
        add_executable(QTPhrasedml WIN32 MACOSX_BUNDLE ${QTPHRASEDML_SOURCES} ${QTPHRASEDML_MOC_SRCS} ${QTPHRASEDML_FORMS_HEADERS} ${QTPHRASEDML_HEADERS} ${QTPHRASEDML_RESOURCE})
        target_link_libraries(QTPhrasedml ${QTPHRASEDML_LIBRARIES} )
        add_definitions(${QT_DEFINITIONS} ${SBW_DEFINITIONS})
        set(MACOSX_BUNDLE_ICON_FILE ${QTPHRASEDML_SRC_DIR}phrasedml.icns)
        install(TARGETS QTPhrasedml DESTINATION bin)
        install(FILES ${QTPHRASEDML_SRC_DIR}phrasedml.ico DESTINATION bin)

endif(WITH_QTPHRASEDML)


####################################################################
#
# Set up remaining variables, add option for universal binaries
#
if(UNIX)
    if(APPLE)
        add_definitions(-DMACOSX)
        #create universal binaries
                option(ENABLE_UNIVERSAL "Create Universal Binaries" OFF)

                set(CMAKE_OSX_ARCHITECTURES "${CMAKE_OSX_ARCHITECTURES}" CACHE STRING "A semicolon separated list of build architectures to be used")
                if(ENABLE_UNIVERSAL)
                  # if universal binaries are requested and none defined so far
                  # overwrite them with all three common architectures. If the user
                  # specified their own list of architectures do not touch!
                  if (CMAKE_OSX_ARCHITECTURES STREQUAL "")
                    set(CMAKE_OSX_ARCHITECTURES "i386;ppc;x86_64" CACHE STRING "A semicolon separated list of build architectures to be used" FORCE)
                  endif()
                endif(ENABLE_UNIVERSAL)
    else(APPLE)
        add_definitions(-DLINUX)
    endif(APPLE)
   # add_definitions( -DPACKAGE_VERSION=\"${PACKAGE_VERSION}\"  -DPACKAGE_NAME="${PROJECT_NAME}")

else(UNIX)
    add_definitions(-DWIN32 -DLIBPHRASEDML_EXPORTS -DLIBLAX_EXPORTS)
    if(MSVC)
      add_definitions(-D_CRT_SECURE_NO_WARNINGS)
      option(WITH_STATIC_RUNTIME "Compile using the static MSVC Runtime" OFF)
      if (WITH_STATIC_RUNTIME)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)

            if(${flag_var} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
        add_definitions( -D_MT)
      endif(WITH_STATIC_RUNTIME)
    endif(MSVC)


endif(UNIX)

###############################################################################
#
# Install win32 dependencies
#
if (NOT UNIX)
   file(GLOB win_dependencies "${CMAKE_SOURCE_DIR}/win32/*.dll" "${CMAKE_CURRENT_SOURCE_DIR}/win32/README.txt")
   if (NOT WITH_STATIC_SBML)
      list(APPEND win_dependencies ${LIBSBML_DLL})
   endif()
   if (NOT WITH_STATIC_SEDML)
      list(APPEND win_dependencies ${LIBSEDML_DLL})
   endif()
   if (NOT WITH_STATIC_NUML)
      list(APPEND win_dependencies ${LIBNUML_DLL})
   endif()
   install(FILES ${win_dependencies} DESTINATION bin/)
endif()

    message(STATUS "  main program include directories = ${INCLUDE_DIRECTORIES}")
