cmake_minimum_required(VERSION 3.0)

#------------------------------------------------
# Project + basics
#

# Project name
# Serves as basis for the package name
project(Fonts)

# Library namespace sequence
set(NAMESPACE GPC)

# Package prefix
# (if none is provided, will be derived from namespace sequence)
set(PACKAGE_PREFIX "GPC")

# Project version (as a string)
set(VERSION "0.0.1")

# Library dependency list
set(IMPORT_PACKAGES)
set(IMPORT_TARGETS)

#--------------------------------------------------------------------------------------
# DO NOT EDIT PAST THIS POINT
#--------------------------------------------------------------------------------------

include("CMakeProject.cmake")
