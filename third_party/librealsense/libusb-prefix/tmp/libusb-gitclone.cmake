
if(NOT "C:/GIT/librealsense/build/libusb-prefix/src/libusb-stamp/libusb-gitinfo.txt" IS_NEWER_THAN "C:/GIT/librealsense/build/libusb-prefix/src/libusb-stamp/libusb-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'C:/GIT/librealsense/build/libusb-prefix/src/libusb-stamp/libusb-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/GIT/librealsense/build/third-party/libusb"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/GIT/librealsense/build/third-party/libusb'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe"  clone --no-checkout "https://github.com/libusb/libusb.git" "libusb"
    WORKING_DIRECTORY "C:/GIT/librealsense/build/third-party"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/libusb/libusb.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe"  checkout 2a7372db54094a406a755f0b8548b614ba8c78ec --
  WORKING_DIRECTORY "C:/GIT/librealsense/build/third-party/libusb"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '2a7372db54094a406a755f0b8548b614ba8c78ec'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe"  submodule update --recursive --init 
    WORKING_DIRECTORY "C:/GIT/librealsense/build/third-party/libusb"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/GIT/librealsense/build/third-party/libusb'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "C:/GIT/librealsense/build/libusb-prefix/src/libusb-stamp/libusb-gitinfo.txt"
    "C:/GIT/librealsense/build/libusb-prefix/src/libusb-stamp/libusb-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/GIT/librealsense/build/libusb-prefix/src/libusb-stamp/libusb-gitclone-lastrun.txt'")
endif()

