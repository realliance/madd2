cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
include(ProcessorCount)
project(madd2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(PACKAGE_TESTS "Build the tests" OFF)
option(USE_CLANG_TIDY "Use Clang Tidy" ON)
option(CI_CLANG_FORMAT_FLAGS "Use CI Clang Format Flags" OFF)

if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(${madd2_SOURCE_DIR}/tests)
endif()

ProcessorCount(N)
if(NOT N EQUAL 0)
  set(CTEST_BUILD_FLAGS -j${N})
  set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N})
endif()

find_program(iwyu_path NAMES include-what-you-use iwyu  REQUIRED)

find_program(clang_format_path NAMES clang-format-10 clang-format REQUIRED)

if (USE_CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
  )
endif()


add_library(madd2 "")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(madd2 PRIVATE -Wall -Wmost -Wextra -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(madd2 PRIVATE -Wall -Wextra)
endif()

add_subdirectory(${madd2_SOURCE_DIR}/libraries)
add_subdirectory(${madd2_SOURCE_DIR}/include)
add_subdirectory(${madd2_SOURCE_DIR}/src)

target_link_libraries(madd2 PRIVATE ${CMAKE_DL_LIBS})
target_include_directories(madd2 INTERFACE "${madd2_SOURCE_DIR}/include")

set_property(TARGET madd2 PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
get_target_property(_sources madd2 SOURCES)

add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  VERBATIM
)

add_custom_target(
  tidy
  COMMAND clang-tidy
    --quiet --warnings-as-errors=* -p ${madd2_BINARY_DIR} ${_sources}
  WORKING_DIRECTORY ${madd2_SOURCE_DIR}
  VERBATIM
)

add_custom_target(
  fix
  COMMAND clang-tidy
    --quiet --fix --fix-errors -p ${madd2_BINARY_DIR} ${_sources}
  WORKING_DIRECTORY ${madd2_SOURCE_DIR}
  VERBATIM
)

if(CI_CLANG_FORMAT_FLAGS)
  set(CLANG_FORMAT_FLAGS 
    --verbose;
    --Werror;
    -i;
    -n;
  )
else()
  set(CLANG_FORMAT_FLAGS
    --verbose;
    -i;
  )
endif()

add_custom_target(
  format
  ALL
  COMMAND ${clang_format_path} ${CLANG_FORMAT_FLAGS}
     ${_sources}
  WORKING_DIRECTORY ${madd2_SOURCE_DIR}
  VERBATIM
)
