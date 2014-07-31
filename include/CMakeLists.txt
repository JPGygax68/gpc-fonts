set(TARGET_NAME "gpc_fonts")

set(TARGET_SET "${TARGET_NAME}")

#------------------------------------------------
# Target: header-only library
#

add_library(${TARGET_NAME} INTERFACE)

# This is probably superfluous, CMake rules would have it look at ${CMAKE_INSTALL_PREFIX}/include anyway:
target_include_directories(${TARGET_NAME} INTERFACE $<INSTALL_INTERFACE:include>)

#------------------------------------------------
# Installing
#

# Note: we use "gpc" as a vendor prefix (subdir in include directory e.a.)
# TODO: define prefixes in parent CMake list ?

install(TARGETS ${TARGET_NAME}
	EXPORT ${TARGET_NAME}-targets # create an "export set" (a "targets" file)
)

install(DIRECTORY gpc DESTINATION "${INSTALL_INCLUDE_DIR}")

# Install the export set for use with the install-tree
install(EXPORT ${TARGET_NAME}-targets DESTINATION "${INSTALL_CMAKE_DIR}")

# Create a config file for the install tree:
set(TARGETSET_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(TARGETSET_LIB_DIR     ${CMAKE_INSTALL_PREFIX}/lib)
set(TARGETSET_CMAKE_DIR   ${CMAKE_INSTALL_PREFIX}/CMake)
configure_file(${TARGET_NAME}-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${TARGET_NAME}-config.cmake
  @ONLY)
  
# ... and install it
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${TARGET_NAME}-config.cmake
  DESTINATION CMake)

#------------------------------------------------
# Exporting the build tree
#

# We use the short form here (ie. "EXPORT" instead of "TARGETS": we reuse the target set defined by install(TARGETS..):
export(EXPORT ${TARGET_NAME}-targets)

# Registers the build tree (of this sub-project) with a global CMake registry:
export(PACKAGE ${TARGET_NAME})

# Create a config file for build tree usage:
set(TARGET_SET "${TARGET_NAME}")
set(TARGETSET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TARGETSET_LIB_DIR     ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(TARGETSET_CMAKE_DIR   ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${TARGET_NAME}-config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}-config.cmake @ONLY)