
include(cmakego)

usepackage(opencv REQUIRED)
add_definitions(--std=c++11)
add_library(replacer SHARED replacer.cpp)
if(LINUX)
	target_link_libraries(replacer dl)
endif()

add_executable(test test.cpp)
target_link_libraries(test p::opencv)
