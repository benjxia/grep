cmake_minimum_required(VERSION 3.22)
project(grep)

set(CMAKE_CXX_STANDARD 17)

add_executable(grep main.cpp str_search/aho_corasick.cpp str_search/aho_corasick.h cmd_parse/parse.cpp cmd_parse/parse.h)
