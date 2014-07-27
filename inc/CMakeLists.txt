#------------------------------------------------
# Target: header-only library
#

file(GLOB HEADERS *.hpp)

add_library(gpc_fonts INTERFACE)

#------------------------------------------------
# Installing
#

# Note: we use "gpc" as a vendor prefix (subdir in include directory e.a.)
# TODO: define prefixes in parent CMake list ?

install(TARGETS gpc_fonts
	EXPORT GPCFonts # create an "export set"
)

install(FILES ${HEADERS} DESTINATION "${INSTALL_INCLUDE_DIR}/gpc/")

 # Install the export set for use with the install-tree
install(EXPORT GPCFonts DESTINATION "${INSTALL_CMAKE_DIR}")

#------------------------------------------------
# Exporting the build tree
#

# Export the package for use from the build tree
# (registers the build tree with a global CMake registry)
export(PACKAGE GPCFonts)
