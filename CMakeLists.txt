cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
project(madd2)
include(FetchContent)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

find_package(PkgConfig)

add_library(madd2 "")
add_subdirectory(${madd2_SOURCE_DIR}/libraries)
add_subdirectory(${madd2_SOURCE_DIR}/include)
add_subdirectory(${madd2_SOURCE_DIR}/src)

option(PACKAGE_TESTS "Build the tests" OFF)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
		add_subdirectory(${madd2_SOURCE_DIR}/tests)
endif()

target_link_libraries(madd2 
	PUBLIC 
	PRIVATE 
		${CMAKE_DL_LIBS}
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_compile_options(madd2 PRIVATE -Wall -Wmost -Wextra -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(madd2 PRIVATE -Wall -Wextra)
endif()

target_include_directories(madd2 INTERFACE "${madd2_SOURCE_DIR}/include")

find_program(iwyu_path NAMES include-what-you-use iwyu  REQUIRED)
set_property(TARGET madd2 PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
