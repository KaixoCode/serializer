cmake_minimum_required (VERSION 3.0)
project (serializer)

set (CMAKE_CXX_STANDARD 23)

option(BUILD_SERIALIZER_EXAMPLE "Build the serializer example project" false)

if (TARGET serializer)
else()
file(GLOB_RECURSE SOURCE
  "${serializer_SOURCE_DIR}/include/*.hpp"
)
endif()

add_library(serializer ${SOURCE})
set_target_properties(serializer PROPERTIES LINKER_LANGUAGE CXX)

if (${BUILD_SERIALIZER_EXAMPLE})
if (TARGET serializer_example)
else()
add_executable(serializer_example
  ${serializer_SOURCE_DIR}/example.cpp
)

target_include_directories(serializer_example PRIVATE
  ${serializer_SOURCE_DIR}/include/
  ${type_utils_SOURCE_DIR}/include/
)
endif()
endif()
