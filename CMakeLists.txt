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
SET(LIBPHRASEDML_VERSION_MINOR 0)
SET(LIBPHRASEDML_VERSION_PATCH ".4")
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
OPTION(WITH_LIBSBML_EXPAT  "Set if libsbml was compiled with a separate expat library."  OFF)
OPTION(WITH_LIBSBML_LIBXML "Set if libsbml was compiled with a separate libxml library." ON)
OPTION(WITH_LIBSBML_XERCES "Set if libsbml was compiled with a separate xerces library." OFF)
OPTION(WITH_LIBSBML_COMPRESSION "Set if libsbml was compiled with separate zdll and bzip libraries." OFF)
OPTION(PHRASEDML_ENABLE_XPATH_EVAL "Use libxml2 for xpath evaluation." OFF)

set(EXTRA_LIBS "" CACHE STRING "Libraries the other libraries depend on that are in non-standard locations" )

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

####################################################################
#
# Locate libsedml
#
    find_path(LIBSEDML_INSTALL_DIR
    NAMES include/sedml/SedBase.h
    PATHS /usr /usr/local /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/
              ${CMAKE_SOURCE_DIR}/../
              )

    if(WITH_STATIC_SEDML)
        find_library(LIBSEDML_LIBRARY
             NAMES libsedml-static.lib libsedml-static.so libsedml-static sedml-static.lib sedml-static.so sedml-static
             PATHS /usr/lib /usr/local/lib
               ${LIBSEDML_INSTALL_DIR}/lib
               ${CMAKE_SOURCE_DIR}
               ${CMAKE_SOURCE_DIR}/dependencies/lib
             )
    else()
        find_library(LIBSEDML_LIBRARY
            NAMES libsedml.lib libsedml.so libsedml sedml.lib sedml.so sedml
            PATHS /usr/lib /usr/local/lib
              ${LIBSEDML_INSTALL_DIR}/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
            )
    endif()
    find_path(LIBSEDML_INCLUDE_DIR
        NAMES sedml/SedBase.h
        PATHS /usr/include /usr/local/include
              ${LIBSEDML_INSTALL_DIR}/include
              ${CMAKE_SOURCE_DIR}/include
              ${CMAKE_SOURCE_DIR}/dependencies/include
        )
    set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${LIBSEDML_LIBRARY} )
    if(WIN32 AND NOT(WITH_STATIC_SEDML))
        find_path(LIBSEDML_BIN_DIR
            NAMES libsedml.dll
            PATHS /usr/bin /usr/local/bin
                  ${LIBSEDML_INSTALL_DIR}/bin
                  ${LIBSEDML_INCLUDE_DIR}/../bin
                  ${CMAKE_SOURCE_DIR}/
                  ${CMAKE_SOURCE_DIR}/dependencies/libsedml/bin
            )
        set(LIBSEDML_DLL ${LIBSEDML_BIN_DIR}/libsedml.dll)
    endif()
    INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${LIBSEDML_INCLUDE_DIR})

####################################################################
#
# Locate libnuml
#
    find_path(LIBNUML_INSTALL_DIR
    NAMES include/numl/NMBase.h
    PATHS /usr /usr/local /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/
              ${CMAKE_SOURCE_DIR}/../
              )

    if(WITH_STATIC_NUML)
        find_library(LIBNUML_LIBRARY
             NAMES libnuml-static.lib libnuml-static.so libnuml-static numl-static.lib numl-static.so numl-static
             PATHS /usr/lib /usr/local/lib
               ${LIBNUML_INSTALL_DIR}/lib
               ${CMAKE_SOURCE_DIR}
               ${CMAKE_SOURCE_DIR}/dependencies/lib
             )
    else()
        find_library(LIBNUML_LIBRARY
            NAMES libnuml.lib libnuml.so libnuml numl.lib numl.so numl
            PATHS /usr/lib /usr/local/lib
              ${LIBNUML_INSTALL_DIR}/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
            )
    endif()
    find_path(LIBNUML_INCLUDE_DIR
        NAMES numl/NMBase.h
        PATHS /usr/include /usr/local/include
              ${LIBNUML_INSTALL_DIR}/include
              ${CMAKE_SOURCE_DIR}/include
              ${CMAKE_SOURCE_DIR}/dependencies/include
        )
    set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${LIBNUML_LIBRARY} )
    if(WIN32 AND NOT(WITH_STATIC_NUML))
        find_path(LIBNUML_BIN_DIR
            NAMES libnuml.dll
            PATHS /usr/bin /usr/local/bin
                  ${LIBNUML_INSTALL_DIR}/bin
                  ${LIBNUML_INCLUDE_DIR}/../bin
                  ${CMAKE_SOURCE_DIR}/
                  ${CMAKE_SOURCE_DIR}/dependencies/libnuml/bin
            )
        set(LIBNUML_DLL ${LIBNUML_BIN_DIR}/libnuml.dll)
    endif()
    INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${LIBNUML_INCLUDE_DIR})

####################################################################
#
# Locate libsbml
#

    find_path(LIBSBML_INSTALL_DIR
    NAMES include/sbml/SBMLTypes.h
    PATHS /usr /usr/local /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/
              ${CMAKE_SOURCE_DIR}/../libsbml-5/release/
              ${CMAKE_SOURCE_DIR}/../
              )

    if(WITH_STATIC_SBML)
        find_library(LIBSBML_LIBRARY
             NAMES libsbml-static.lib libsbml-static.so libsbml-static sbml-static.lib sbml-static.so sbml-static
             PATHS /usr/lib /usr/local/lib
               ${LIBSBML_INSTALL_DIR}/lib
               ${CMAKE_SOURCE_DIR}
               ${CMAKE_SOURCE_DIR}/dependencies/lib
               ${CMAKE_SOURCE_DIR}/../libsbml-5/release/lib/
             )
    else()
        find_library(LIBSBML_LIBRARY
            NAMES libsbml.lib libsbml.so libsbml sbml.lib sbml.so sbml
            PATHS /usr/lib /usr/local/lib
              ${LIBSBML_INSTALL_DIR}/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              ${CMAKE_SOURCE_DIR}/../libsbml-5/release/lib/
            )
    endif()
    find_path(LIBSBML_INCLUDE_DIR
        NAMES sbml/SBMLTypes.h
        PATHS /usr/include /usr/local/include
              ${LIBSBML_INSTALL_DIR}/include
              ${CMAKE_SOURCE_DIR}/include
              ${CMAKE_SOURCE_DIR}/dependencies/include
              ${CMAKE_SOURCE_DIR}/../libsbml-5/release/include/
        )
    set(LIBPHRASEDML_LIBS ${LIBSBML_LIBRARY} ${LIBPHRASEDML_LIBS} )
    if(WIN32 AND NOT WITH_STATIC_SBML)
        find_path(LIBSBML_BIN_DIR
            NAMES libsbml.dll
            PATHS /usr/bin /usr/local/bin
                  ${LIBSBML_INSTALL_DIR}/bin
                  ${LIBSBML_INCLUDE_DIR}/../bin
                  ${CMAKE_SOURCE_DIR}/
                  ${CMAKE_SOURCE_DIR}/dependencies/libsbml/bin
                  ${CMAKE_SOURCE_DIR}/../libsbml-5/release/bin/
            )
        set(LIBSBML_DLL ${LIBSBML_BIN_DIR}/libsbml.dll)
    endif()
    INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${LIBSBML_INCLUDE_DIR})
    if (WITH_COMP_SBML)
        add_definitions( -DUSE_COMP )
    endif(WITH_COMP_SBML)

####################################################################
#
# Locate the CellML API and attendant libraries if needed
#

# [Not needed for phrased-ML at this point]

###############################################################
#
# Locate the libraries libsbml depends on, for static linking.
#

if(WITH_LIBSBML_EXPAT)
    find_library(EXPAT_LIBRARY
        NAMES libexpat.lib libexpat.so libexpat.dylib libexpat expat.lib expat.so expat.dylib expat
	PATHS /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              ${LIBSBML_INCLUDE_DIR}/../lib
        )
    set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${EXPAT_LIBRARY} )
endif()

if(WITH_LIBSBML_LIBXML)
    find_library(LIBXML_LIBRARY
        NAMES libxml2.lib libxml2.so libxml2.dylib libxml2
	PATHS /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              ${LIBSBML_INCLUDE_DIR}/../lib
        )
    set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${LIBXML_LIBRARY} )

    if(WIN32)
      find_library(ICONV_LIBRARY
          NAMES iconv.lib iconv.so iconv.dylib iconv libiconv.lib libiconv.so libiconv.dylib libiconv
          PATHS /usr/lib /usr/local/lib
                ${CMAKE_SOURCE_DIR}
                ${CMAKE_SOURCE_DIR}/dependencies/lib
                ${LIBSBML_INCLUDE_DIR}/../lib
          )
      set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${ICONV_LIBRARY} )
    endif()
endif()

if(WITH_LIBSBML_XERCES)
    find_library(XERCES_LIBRARY
        NAMES xerces-c_static_3.lib xerces-c_static_3.so xerces-c_static_3.dylib xerces-c_static_3
	PATHS /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              ${LIBSBML_INCLUDE_DIR}/../lib
        )
    set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${XERCES_LIBRARY} )
endif()

if(WITH_LIBSBML_COMPRESSION)
    find_library(ZDLL_LIBRARY
        NAMES zdll.lib zdll.so zdll.dylib zdll z
	PATHS /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              ${LIBSBML_INCLUDE_DIR}/../lib
        )
    set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${ZDLL_LIBRARY} )

    find_library(BZIP_LIBRARY
        NAMES bzip2.lib bzip2.so bzip2.dylib bzip2 bz2
	PATHS /usr/lib /usr/local/lib
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              ${LIBSBML_INCLUDE_DIR}/../lib
        )
    set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${BZIP_LIBRARY} )
endif()

###############################################################################
#
# If WITH_SWIG is selected, we need to find swig
#
if(WITH_SWIG)
    find_program(SWIG_EXECUTABLE
        NAMES swig
        PATHS
              "c:/Program Files (x86)/Swig"
              c:/Program Files/Swig
              c:/swigwin-2.0.11
              c:/swigwin-2.0.10
              c:/swigwin-2.0.9
              c:/swigwin-2.0.8
              c:/swigwin-2.0.7
              c:/swigwin-2.0.6
              c:/swigwin-2.0.5
              c:/swigwin-2.0.4
              c:/swigwin-2.0.3
              c:/swigwin-2.0.2
              c:/swigwin-2.0.1
              c:/swigwin-2.0.0
              /usr/local/bin
              /opt/local/bin
              /usr/bin
        DOC "The file name of the swig executable."
        )
    find_package(SWIG)
    set(SWIG_EXTRA_ARGS "" CACHE STRING "Extra arguments to SWIG" )
endif(WITH_SWIG)

if(WITH_SWIG)
    message(STATUS "  Using SWIG                    = ${SWIG_EXECUTABLE}")

    if (SWIG_FOUND AND SWIG_VERSION VERSION_LESS "2.0.4")
        message(WARNING "   You are using swig version ${SWIG_VERSION} while we recommend at least version 2.0.4.")
    endif()

endif()

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
