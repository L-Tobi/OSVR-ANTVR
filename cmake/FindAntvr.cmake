#==================================================================================
#try to find ANTVRHidApi
# Original Author:
#2016 PengHui Liu <liupenghui@antvr.com>
#Distributed under the Boost Software License, Version 1.0.
#==================================================================================

set(ANTVR_ROOT_DIR
	"$(ANTVR_ROOT_DIR)"
	CACHE
	PATH
	"find ANTVR SDK")

if(WIN32)
	#check system 32/64 bits
	if("$(CMAKE_SIZEOF_VOID_P" EQUAL "8")
		set(ANTVR_LIBRARY_PATH_SUFFIX "dll/x64")
	else()
		set(ANTVR_LIBRARY_PATH_SUFFIX "dll")
	endif()
	
	set(_ANTVR_ENV "ProgramFiles(x86)")
	set(_ANTVR $ENV{${_ANTVR_ENV}})
	
	if(NOT "$ENV{${_ANTVR_ENV}}" STREQUAL "")
		file(TO_CMAKE_PATH "$ENV{${_ANTVR_ENV}}" programfile)
	else()
		file(TO_CMAKE_PATH "$ENV{ProgramFiles}" programfile)
	endif()

	find_library(ANTVR_ANTVRHIDAPI_LIBRARY
	NAMES
	ANTVRHidApi
	PATHS
	"${ANTVR_ROOT_DIR}"
	"${programfile}/ANTVR Corproration/ANTVRSDK"
	PATH_SUFFIXES
	${ANTVR_LIBRARY_PATH_SUFFIX})
	if(ANTVR_ANTVRHIDAPI_LIBRARY)
		get_filename_component(_libdir "${ANTVR_ANTVRHIDAPI_LIBRARY}" DIRECTORY)
	endif()
	find_path(ANTVR_INCLUDE_DIR
		NAMES
		ANTVRSDK.h
		HINTS
		${_libdir}
		PATHS
		"${ANTVR_ROOT_DIR}"
		"${programfile}/ANTVR Corproration/ANTVRSDK"
		)
		
endif() #WIN32

#list(APPEND XRANDR_LIBRARIES ${ANTVR_INCLUDE_DIR})


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ANTVR
	FOUND_VAR 
	ANTVR_FOUND
	REQUIRED_VARS
	ANTVR_ANTVRHIDAPI_LIBRARY
	ANTVR_INCLUDE_DIR
	)

if(ANTVR_FOUND)

	set(ANTVR_INCLUDE_DIRS ${ANTVR_INCLUDE_DIR})
	if(NOT TARGET ANTVR::ANTVRHidApi)
		add_library(ANTVR::ANTVRHidApi UNKNOWN IMPORTED)
		set_target_properties(ANTVR::ANTVRHidApi 
			PROPERTIES
			IMPORTED_LOCATION "${ANTVR_ANTVRHIDAPI_LIBRARY}"
			INTERFACE_INCLUDE_DIRECTORIES "${ANTVR_INCLUDE_DIRS}")
			
	endif()
	mark_as_advanced(ANTVR_ROOT_DIR)
endif()

mark_as_advanced(ANTVR_INCLUDE_DIR
	ANTVR_ANTVRHIDAPI_LIBRARY
	)