## @file    CMakeLists.txt
## @brief   CMake build script
## @author  Lucian Smith

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h )

set(TEST_FILES ${CPP_FILES} ${H_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(BEFORE ${LIBSBML_ROOT_SOURCE_DIR}/src)
include_directories(BEFORE ${LIBSBML_ROOT_BINARY_DIR}/src)

#This program needs Antimony to function:
    find_path(LIBANTIMONY_INSTALL_DIR
    NAMES include/antimony/antimony_api.h
    PATHS /usr /usr/local /usr/lib /usr/local/lib 
              ${CMAKE_SOURCE_DIR}
              ${CMAKE_SOURCE_DIR}/dependencies/
              ${CMAKE_SOURCE_DIR}/../
              )

    find_library(LIBANTIMONY_LIBRARY
         NAMES libantimony-static.lib libantimony-static.so libantimony-static antimony-static.lib antimony-static.so antimony-static
         PATHS /usr/lib /usr/local/lib
           ${LIBANTIMONY_INSTALL_DIR}/lib
           ${CMAKE_SOURCE_DIR}
           ${CMAKE_SOURCE_DIR}/dependencies/lib
         )
    find_path(LIBANTIMONY_INCLUDE_DIR
        NAMES antimony_api.h
        PATHS /usr/include /usr/local/include 
              ${LIBANTIMONY_INSTALL_DIR}/include
              ${CMAKE_SOURCE_DIR}/include 
              ${CMAKE_SOURCE_DIR}/dependencies/include
        )
    set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${LIBANTIMONY_LIBRARY} )
    INCLUDE_DIRECTORIES(${LIBANTIMONY_INCLUDE_DIR})

####################################################################
#
# Locate the CellML API and attendant libraries if needed
#
        find_path(CELLML_API_INSTALL_DIR
        NAMES include/IfaceCellML_APISPEC.hxx
        PATHS /usr/include /usr/local/include 
              "C:/Program Files (x86)/cellml-sdk-1.11"
              C:/Program Files/cellml-sdk-1.11
              ${CMAKE_SOURCE_DIR}/cellml-sdk 
              ${CMAKE_SOURCE_DIR}/dependencies/cellml-sdk
              )

        find_library(CELLML_API_LIB
        NAMES cellml.lib cellml
        PATHS /usr/lib /usr/local/lib
              ${CELLML_API_INSTALL_DIR}/lib
              C:/build/cellml-api/.libs/
              ${CMAKE_SOURCE_DIR} 
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              )
        set(ALL_CELLML_LIBS ${ALL_CELLML_LIBS} ${CELLML_API_LIB})

        find_library(CEVAS_LIB 
        NAMES cevas.lib cevas
        PATHS /usr/lib /usr/local/lib
              ${CELLML_API_INSTALL_DIR}/lib
              ${CMAKE_SOURCE_DIR} 
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              )
        set(ALL_CELLML_LIBS ${ALL_CELLML_LIBS} ${CEVAS_LIB})
    
        find_library(ANNOTOOLS_LIB 
        NAMES annotools.lib annotools
        PATHS /usr/lib /usr/local/lib
              ${CELLML_API_INSTALL_DIR}/lib
              ${CMAKE_SOURCE_DIR} 
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              )
        set(ALL_CELLML_LIBS ${ALL_CELLML_LIBS} ${ANNOTOOLS_LIB})
    
    find_library(CUSES_LIB 
        NAMES cuses.lib cuses
        PATHS /usr/lib /usr/local/lib
              ${CELLML_API_INSTALL_DIR}/lib
              ${CMAKE_SOURCE_DIR} 
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              )
        set(ALL_CELLML_LIBS ${ALL_CELLML_LIBS} ${CUSES_LIB})

        find_library(TELICEMS_LIB 
        NAMES telicems.lib telicems
        PATHS /usr/lib /usr/local/lib
              ${CELLML_API_INSTALL_DIR}/lib
              ${CMAKE_SOURCE_DIR} 
              ${CMAKE_SOURCE_DIR}/dependencies/lib
              )
        set(ALL_CELLML_LIBS ${ALL_CELLML_LIBS} ${TELICEMS_LIB})

        set(CELLML_INCLUDE_DIRECTORIES ${CELLML_API_INSTALL_DIR}/include )

        set(LIBPHRASEDML_LIBS ${LIBPHRASEDML_LIBS} ${ALL_CELLML_LIBS} )
        INCLUDE_DIRECTORIES(${CELLML_INCLUDE_DIRECTORIES} )

if (EXTRA_INCLUDE_DIRS) 
 include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

add_executable(create-test-suite ${TEST_FILES})
target_link_libraries(create-test-suite ${LIBPHRASEDML_LIBRARY}-static ${LIBANTIMONY_LIBRARY} ${LIBPHRASEDML_LIBS})

install(TARGETS create-test-suite DESTINATION bin)
