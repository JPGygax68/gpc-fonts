
#-----------------------------------------------
# Compute derived variables
#

# Namespace
set(NAMESPACE_STRING)
set(NAMESPACE_PREFIX)
if (NAMESPACE)
	string(REPLACE ";" "::" NAMESPACE_STRING "${NAMESPACE}")
	string(REPLACE ";" "_" NAMESPACE_PREFIX "${NAMESPACE}")
	set(NAMESPACE_STRING "${NAMESPACE_STRING}::")
	set(NAMESPACE_PREFIX "${NAMESPACE_PREFIX}_")
endif()
string(TOLOWER ${NAMESPACE_STRING} NAMESPACE_STRING_LC)
#message("NAMESPACE_STRING: ${NAMESPACE_STRING}")
#message("NAMESPACE_STRING_LC: ${NAMESPACE_STRING_LC}")
#message("NAMESPACE_PREFIX: ${NAMESPACE_PREFIX}")

# Package prefix
if (NOT PACKAGE_PREFIX)
	set(PACKAGE_PREFIX ${NAMESPACE_PREFIX})
endif()

# Package identifier
set(PACKAGE_ID "${PACKAGE_PREFIX}${PROJECT_NAME}")

# Version string
string(REPLACE ";" "." VERSION_STRING "${VERSION}")

#-----------------------------------------------
# Installation paths
#

# Offer the user the choice of overriding the installation directories
#set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
#set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
	set(DEF_INSTALL_CMAKE_DIR CMake)
else()
	set(DEF_INSTALL_CMAKE_DIR lib/CMake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")
 
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
	set(var INSTALL_${p}_DIR)
	if(NOT IS_ABSOLUTE "${${var}}")
		set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
	endif()
endforeach()

#------------------------------------------------
# Target: header-only library
#

add_subdirectory(include)

#------------------------------------------------
# Tests
#

enable_testing()

add_custom_target(build_and_test "${CMAKE_CTEST_COMMAND} -V")

add_subdirectory(tests)
