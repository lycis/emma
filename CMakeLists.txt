cmake_minimum_required(VERSION 3.5)
project(emma)
file(GLOB emma_src "*.h" "*.c")
add_library(emma STATIC ${emma_src})
