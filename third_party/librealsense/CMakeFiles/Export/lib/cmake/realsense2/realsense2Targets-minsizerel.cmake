#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "realsense2::realsense-file" for configuration "MinSizeRel"
set_property(TARGET realsense2::realsense-file APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(realsense2::realsense-file PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "C;CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/realsense-file.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS realsense2::realsense-file )
list(APPEND _IMPORT_CHECK_FILES_FOR_realsense2::realsense-file "${_IMPORT_PREFIX}/lib/realsense-file.lib" )

# Import target "realsense2::realsense2" for configuration "MinSizeRel"
set_property(TARGET realsense2::realsense2 APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(realsense2::realsense2 PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/realsense2.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/realsense2.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS realsense2::realsense2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_realsense2::realsense2 "${_IMPORT_PREFIX}/lib/realsense2.lib" "${_IMPORT_PREFIX}/bin/realsense2.dll" )

# Import target "realsense2::fw" for configuration "MinSizeRel"
set_property(TARGET realsense2::fw APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(realsense2::fw PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "C"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/fw.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS realsense2::fw )
list(APPEND _IMPORT_CHECK_FILES_FOR_realsense2::fw "${_IMPORT_PREFIX}/lib/fw.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
