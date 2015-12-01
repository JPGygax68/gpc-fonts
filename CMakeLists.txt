# Adapted from https://github.com/ComicSansMS/libstratcom/blob/master/CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

# Project name
project(libGPCFonts CXX)

# List of header files (header-only library)
set(HEADER_FILES
  include/gpc/fonts/rasterized_font.hpp 
  include/gpc/fonts/character_range.hpp 
  include/gpc/fonts/character_set.hpp 
  include/gpc/fonts/bounding_box.hpp 
  include/gpc/fonts/rasterized_glyph_cbox.hpp 
  include/gpc/fonts/cereal.hpp
)

# Create the (main) target
add_library(libGPCFonts INTERFACE)

if(MSVC)
    target_compile_options(libGPCFonts INTERFACE /DNOMINMAX /W4)
else()
    target_compile_options(libGPCFonts INTERFACE -pedantic -Wall -std=c++11)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(libGPCFonts INTERFACE -stdlib=libc++)
    endif()
endif()

target_include_directories(libGPCFonts INTERFACE $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

add_executable(testsuite testsuite/test.cpp ${HEADER_FILES})
target_link_libraries(testsuite libGPCFonts)

# Boost
if (NOT BOOST_ROOT)
	set(BOOST_ROOT $ENV{BOOST_ROOT})
endif()
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
target_include_directories(testsuite PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(testsuite ${Boost_LIBRARIES})

add_test(NAME testsuite COMMAND testsuite CONFIGURATIONS Debug)

#------------------------------------------------
# Installation - specify files to package

install(TARGETS libGPCFonts EXPORT libGPCFontsTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)
# TODO: test this, destination paths might be wrong
install(FILES ${HEADER_FILES} DESTINATION include/gpc/fonts)
include(CmakePackageConfigHelpers)

# installation - build tree specific package config files
export(EXPORT libGPCFontsTargets FILE ${CMAKE_BINARY_DIR}/libGPCFontsTargets.cmake)
set(PACKAGE_NAME libGPCFonts)
configure_file(${PROJECT_SOURCE_DIR}/ProjectConfig.cmake.in
    ${CMAKE_BINARY_DIR}/libGPCFontsConfig.cmake
    @ONLY
)

#------------------------------------------------
# Export build tree
#

export(PACKAGE libGPCFonts)

# installation - relocatable package config files
configure_package_config_file(${PROJECT_SOURCE_DIR}/ProjectConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/libGPCFontsConfig.cmake
  INSTALL_DESTINATION cmake
)

#------------------------------------------------
# Installation (final part)
#

install(EXPORT libGPCFontsTargets
  FILE libGPCFontsTargets.cmake
  DESTINATION "cmake"
)
install(FILES
  ${CMAKE_BINARY_DIR}/cmake/libGPCFontsConfig.cmake
  DESTINATION "cmake"
)
