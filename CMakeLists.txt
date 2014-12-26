# Adapted from https://github.com/ComicSansMS/libstratcom/blob/master/CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

# Project name
project(libGPCFonts)

# Version (semantic: major, minor, patch-level)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# Package name: define here if project name is not sufficiently unique
#set(PACKAGE_NAME GPCFonts)

# Source & header files
#set(SOURCE_FILES mylibrary.cpp)
set(HEADER_FILES RasterizedFont.hpp CharacterRange.hpp CharacterSet.hpp RasterizedGlyphCBox.hpp cereal.hpp)

# Namespace (container for include files, added to include directory; e.g. "nslevel1/nslevel2")
# TODO: make the trailing double colon automatic
set(NAMESPACE GPC::Fonts::)

# Subdirectory (below "include") for header files (will be derived from namespace if not specified)
# DO NOT FORGET to adapt in filesystem too
#set(HEADERS_SUBDIRECTORY "nslevel1/nslevel2")

# Define this if the target name can't or shouldn't be derived from the project name
#set(TARGET_NAME MyLibrary)




#----------------------------------------------------------------------
# ONLY EDIT PAST THIS POINT IF CUSTOM CONFIGURATION IS NEEDED
#----------------------------------------------------------------------

# Assemble version components into single string
set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
# Undefine so as not to pass into subprojects
set(VERSION_MAJOR)
set(VERSION_MINOR)
set(VERSION_PATCH)

# Check that we have a package name, use the project name otherwise
if (NOT PACKAGE_NAME)
  set(PACKAGE_NAME ${PROJECT_NAME})
endif()

# Derive headers subdirectory from namespace (unless explicitly specified)
if (NOT HEADERS_SUBDIRECTORY)
  string(REPLACE "::" ";" parts ${NAMESPACE}) 
  foreach(part ${parts})
    string(TOLOWER ${part} part)
    list(APPEND headers "${part}")
  endforeach()
  string(REPLACE ";" "/" HEADERS_SUBDIRECTORY "${headers}")
  message(STATUS "Headers subdirectory derived from namespace: ${HEADERS_SUBDIRECTORY}")
endif()

# Assemble source file paths
foreach(source ${SOURCE_FILES})
  list(APPEND TARGET_SOURCE_FILES "src/${source}")
endforeach()
set(SOURCE_FILES) # do not pass to subdirs

# Compose header file paths
foreach(header ${HEADER_FILES})
  list(APPEND TARGET_HEADER_FILES "include/${HEADERS_SUBDIRECTORY}/${header}")
endforeach()
set(HEADER_FILES) # do not pass to subdirs

# Check / compute the name of the (main) target
if (NOT TARGET_NAME)
  #string(SUBSTRING ${PROJECT_NAME} 0 3 prefix)
  #if (prefix STREQUAL "lib")
  #  string(SUBSTRING ${PROJECT_NAME} 3 -1 TARGET_NAME)
  #  message(STATUS "Target name derived from project name: ${TARGET_NAME}")
  #else()
    set(TARGET_NAME ${PROJECT_NAME})
  #endif()
endif()

# Create the (main) target
add_library(${TARGET_NAME} INTERFACE)

if(MSVC)
    target_compile_options(${TARGET_NAME} INTERFACE /W4)
else()
    target_compile_options(${TARGET_NAME} INTERFACE -pedantic -Wall -std=c++11)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(${TARGET_NAME} INTERFACE -stdlib=libc++)
    endif()
endif()

target_include_directories(${TARGET_NAME} INTERFACE $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
set_property(TARGET ${TARGET_NAME} PROPERTY INTERFACE_VERSION ${PROJECT_VERSION})
set_property(TARGET ${TARGET_NAME} PROPERTY INTERFACE_SOVERSION ${VERSION_MAJOR})
set_property(TARGET ${TARGET_NAME} PROPERTY INTERFACE_DEBUG_POSTFIX d)

#------------------------------------------------
# Test suite 

# Prerequisites

include(CTest)
#enable_testing()

add_executable(testsuite testsuite/test.cpp)
target_link_libraries(testsuite ${TARGET_NAME})

find_package(Boost) # for some reason, specifying the component (unit_test_framework) won't work
target_include_directories(testsuite PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(testsuite ${Boost_LIBRARIES})

add_test(NAME testsuite COMMAND testsuite CONFIGURATIONS Debug)

#------------------------------------------------
# Installation - specify files to package

install(TARGETS ${TARGET_NAME} EXPORT ${PACKAGE_NAME}Targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)
install(FILES ${TARGET_HEADER_FILES} DESTINATION include/${HEADERS_SUBDIRECTORY})
include(CmakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${PACKAGE_NAME}Version.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

# installation - build tree specific package config files
export(EXPORT ${PACKAGE_NAME}Targets FILE ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}Targets.cmake)
configure_file(${PROJECT_SOURCE_DIR}/ProjectConfig.cmake.in
    ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}Config.cmake
    @ONLY
)

#------------------------------------------------
# Export build tree
#

export(PACKAGE ${PACKAGE_NAME})

# installation - relocatable package config files
configure_package_config_file(${PROJECT_SOURCE_DIR}/ProjectConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PACKAGE_NAME}Config.cmake
  INSTALL_DESTINATION cmake
)

#------------------------------------------------
# Installation (final part)
#

install(EXPORT ${PACKAGE_NAME}Targets
  FILE ${PACKAGE_NAME}Targets.cmake
  DESTINATION "cmake"
)
install(FILES
  ${CMAKE_BINARY_DIR}/cmake/${PACKAGE_NAME}Config.cmake
  ${CMAKE_BINARY_DIR}/cmake/${PACKAGE_NAME}Version.cmake
  DESTINATION "cmake"
)

#------------------------------------------------
# documentation
#

find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(${PACKAGE_NAME}_DOC_DIR ${PROJECT_BINARY_DIR}/doc)
  configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in ${${PACKAGE_NAME}_DOC_DIR}/Doxyfile @ONLY)
  add_custom_target(doxygen-doc
    COMMAND ${DOXYGEN_EXECUTABLE}
    WORKING_DIRECTORY ${${PACKAGE_NAME}_DOC_DIR}
    COMMENT "Building doxygen documentation"
    SOURCES ${PROJECT_SOURCE_DIR}/Doxyfile.in
  )
  source_group("" FILES ${PROJECT_SOURCE_DIR}/Doxyfile.in)
endif()

#-------------------------------------------------
# Example application
#

option(BUILD_EXAMPLE_APPLICATIONS "Check this option to build the sample applications" OFF)
if(BUILD_EXAMPLE_APPLICATIONS)
  add_subdirectory(examples)
  if(WIN32)
    add_custom_command(TARGET stratcom POST_BUILD 
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:stratcom> ${CMAKE_BINARY_DIR}/examples
    )
  endif()
endif()
