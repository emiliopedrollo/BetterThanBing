cmake_minimum_required(VERSION 3.6)
project(BetterThanBing)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -ansi")

set(SOURCE_FILES main.c trie.h trie.c utils.c utils.h lists.c lists.h)
add_executable(btbg ${SOURCE_FILES})