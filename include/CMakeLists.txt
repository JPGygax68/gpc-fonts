set(TARGET_NAME "Fonts")

set(TARGET_SET "${TARGET_NAME}")

set(NAMESPACE "GPC::")
set(PACKAGE_PREFIX "GPC_")

#------------------------------------------------
# Target: header-only library
#

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
# This is probably superfluous, CMake rules would have it look at ${CMAKE_INSTALL_PREFIX}/include anyway:
target_include_directories(${PROJECT_NAME} INTERFACE $<INSTALL_INTERFACE:include>)

#------------------------------------------------
# Installing
#

# Note: we use "gpc" as a vendor prefix (subdir in include directory e.a.)
# TODO: define prefixes in parent CMake list ?

install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}-targets # create an "export set" (a "targets" file)
)

install(DIRECTORY gpc DESTINATION "${INSTALL_INCLUDE_DIR}")

# Install the export set for use with the install-tree
install(EXPORT ${PROJECT_NAME}-targets DESTINATION "${INSTALL_CMAKE_DIR}" NAMESPACE ${NAMESPACE_STRING})

# Create a config file for the install tree:
set(TARGETSET_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(TARGETSET_LIB_DIR     ${CMAKE_INSTALL_PREFIX}/lib)
set(TARGETSET_CMAKE_DIR   ${CMAKE_INSTALL_PREFIX}/CMake)
configure_file(config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${PACKAGE_ID}-config.cmake
  @ONLY)
  
# ... and install it
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${PACKAGE_ID}-config.cmake
  DESTINATION CMake)

#------------------------------------------------
# Exporting the build tree / source tree
#

# We use the short form here (ie. "EXPORT" instead of "TARGETS": we reuse the target set defined by install(TARGETS..):
#export(EXPORT ${PROJECT_NAME}-targets)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}-targets.cmake NAMESPACE ${NAMESPACE_STRING})

# Registers the build tree (of this sub-project) with a global CMake registry:
export(PACKAGE ${PROJECT_NAME})

# Create a config file for build tree usage:
set(TARGET_SET "${PACKAGE_ID}")
set(TARGETSET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TARGETSET_LIB_DIR     ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(TARGETSET_CMAKE_DIR   ${CMAKE_CURRENT_BINARY_DIR})
configure_file(config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_ID}-config.cmake @ONLY)