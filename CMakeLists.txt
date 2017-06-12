cmake_minimum_required(VERSION 3.6)
project(BetterThanBing)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES main.c trie.h trie.c)
add_executable(btb ${SOURCE_FILES})