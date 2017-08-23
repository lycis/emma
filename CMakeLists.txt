cmake_minimum_required(VERSION 3.5)
project(emma)
link_directories(${emma_BINARY_DIR})

file(GLOB emma_src "*.h" "*.c")
add_library(emma STATIC ${emma_src})

file(GLOB emma_test_src "test/*.h" "test/*.c")
add_executable(emma_test ${emma_test_src})
target_link_libraries(emma_test emma)
target_include_directories(emma_test PUBLIC ".")

add_dependencies(emma_test emma)
