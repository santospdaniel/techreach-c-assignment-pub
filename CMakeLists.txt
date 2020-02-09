cmake_minimum_required(VERSION 3.2.2)
project(c-plus-assignment)

## C++11 Flags
#add_compile_options(-std=c++11)
#add_compile_options(-pthread)
#add_compile_options(-Werror=return-type)                   # error on missing return type
#add_compile_options(-Werror=format)                        # error on wrong printf formats
#add_compile_options(-Werror=parentheses)                   # error when using ambiguous syntax

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
