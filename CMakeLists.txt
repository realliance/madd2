cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
project(maddv2)
include(FetchContent)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

find_package(PkgConfig)

add_library(maddv2 "")
add_subdirectory(${maddv2_SOURCE_DIR}/libraries)
add_subdirectory(${maddv2_SOURCE_DIR}/include)
add_subdirectory(${maddv2_SOURCE_DIR}/src)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
		add_subdirectory(${maddv2_SOURCE_DIR}/tests)
endif()

target_link_libraries(maddv2 
	PUBLIC 
		# glad 
		# glfw 
	PRIVATE 
		${CMAKE_DL_LIBS}
)

target_include_directories(maddv2 INTERFACE "${maddv2_SOURCE_DIR}/include")

find_program(iwyu_path NAMES include-what-you-use iwyu  REQUIRED)
set_property(TARGET maddv2 PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_CLANG_TIDY
#   clang-tidy;
#   -header-filter=.;
#   -checks=*;
#   -warnings-as-errors=*;)