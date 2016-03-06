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
  include/gpc/fonts/store.hpp
)

# Create the (main) target
add_library(${PROJECT_NAME} INTERFACE)

if(MSVC)
    target_compile_options(${PROJECT_NAME} INTERFACE /DNOMINMAX /W4)
else()
    target_compile_options(${PROJECT_NAME} INTERFACE -pedantic -Wall -std=c++11)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} INTERFACE -stdlib=libc++)
    endif()
endif()

target_include_directories(${PROJECT_NAME} INTERFACE $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

# Boost
option(libGPCFonts_BUILD_TESTSUITE "Build libGPCFonts test suite" OFF)
if (libGPCFonts_BUILD_TESTSUITE)

  add_executable(gpcfonts_testsuite testsuite/test.cpp ${HEADER_FILES})
  target_link_libraries(gpcfonts_testsuite ${PROJECT_NAME})

  if (NOT BOOST_ROOT)
    set(BOOST_ROOT $ENV{BOOST_ROOT})
  endif()
  set(Boost_USE_MULTITHREADED ON)
  set(Boost_USE_STATIC_LIBS ON)
  find_package(Boost REQUIRED COMPONENTS unit_test_framework)
  target_include_directories(gpcfonts_testsuite PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(gpcfonts_testsuite ${Boost_LIBRARIES})

  add_test(NAME ${PROJECT_NAME}_Test COMMAND gpcfonts_testsuite CONFIGURATIONS Debug)
endif()

if (0)

#------------------------------------------------
# Installation - specify files to package

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)
# TODO: test this, destination paths might be wrong
install(FILES ${HEADER_FILES} DESTINATION include/gpc/fonts)
include(CmakePackageConfigHelpers)

# installation - build tree specific package config files
export(EXPORT ${PROJECT_NAME}-targets FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-targets.cmake)
set(PACKAGE_NAME ${PROJECT_NAME})
configure_file(${PROJECT_SOURCE_DIR}/ProjectConfig.cmake.in
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    @ONLY
)

#------------------------------------------------
# Export build tree
#

export(PACKAGE ${PROJECT_NAME})

# Installation - relocatable package config files
configure_package_config_file(${PROJECT_SOURCE_DIR}/ProjectConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION cmake
)

#------------------------------------------------
# Installation (final part)
#

install(EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  DESTINATION "cmake"
)
install(FILES
  ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}-config.cmake
  DESTINATION "cmake"
)

endif(0) # do not install or export