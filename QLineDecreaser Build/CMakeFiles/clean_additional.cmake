# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QLineDecreaser_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QLineDecreaser_autogen.dir\\ParseCache.txt"
  "QLineDecreaser_autogen"
  )
endif()
