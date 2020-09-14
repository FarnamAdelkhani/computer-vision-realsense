#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "realsense2-gl::realsense2-gl" for configuration "Debug"
set_property(TARGET realsense2-gl::realsense2-gl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(realsense2-gl::realsense2-gl PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/realsense2-gld.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "realsense2::realsense2"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG ""
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/realsense2-gld.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS realsense2-gl::realsense2-gl )
list(APPEND _IMPORT_CHECK_FILES_FOR_realsense2-gl::realsense2-gl "${_IMPORT_PREFIX}/lib/realsense2-gld.lib" "${_IMPORT_PREFIX}/bin/realsense2-gld.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
