#=====================================================================
# ANTVR plugin for OSVR
#=====================================================================
cmake_minimum_required(VERSION 2.8.12)
project(com_osvr_ANTVR) # Change this line.

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# This looks for an osvrConfig.cmake file - most of the time it can be
# autodetected but you might need to create/extend CMAKE_PREFIX_PATH to include something like
# C:/Users/Ryan/Desktop/build/OSVR-Core-vc12 or
# C:/Users/Ryan/Downloads/OSVR-Core-Snapshot-v0.1-406-gaa55515-build54-vs12-32bit
# in the CMake GUI or command line.
find_package(osvr REQUIRED)
find_package(ANTVR REQUIRED)
# This generates a header file, from the named json file, containing a string literal
# named com_osvr_example_selfcontained_json (not null terminated)
# The file must be added as a source file to some target (as below) to be generated.
osvr_convert_json(com_osvr_ANTVR_json
    com_osvr_ANTVR.json
    "${CMAKE_CURRENT_BINARY_DIR}/com_osvr_ANTVR_json.h")

# Be able to find our generated header file.
#include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# This is just a helper function wrapping CMake's add_library command that
# sets up include dirs, libraries, and naming convention (no leading "lib")
# for an OSVR plugin. It also installs the plugin into the right directory.
# Pass as many source files as you need. See osvrAddPlugin.cmake for full docs.
osvr_add_plugin(com_osvr_ANTVR
    com_osvr_ANTVR.cpp
	ANTVRHeadsetTracker.h
    "${CMAKE_CURRENT_BINARY_DIR}/com_osvr_ANTVR_json.h")

# Link against PluginKit (C++ wrapper) and the ANTVR driver.
target_link_libraries(com_osvr_ANTVR
    osvr::osvrPluginKitCpp
    ANTVR::ANTVRHidApi)
# Install docs, license, sample config	
install(FILES
    osvr_server_config.antvr.sample.json
    README.md
    LICENSE
    DESTINATION .)
