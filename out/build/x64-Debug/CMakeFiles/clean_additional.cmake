# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "libs\\CMakeFiles\\QtAppLibrary_autogen.dir\\AutogenUsed.txt"
  "libs\\CMakeFiles\\QtAppLibrary_autogen.dir\\ParseCache.txt"
  "libs\\QtAppLibrary_autogen"
  )
endif()
