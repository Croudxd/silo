cmake_minimum_required(VERSION 3.10)
project(silo VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
    src/main.cpp
    src/vault.cpp
    src/storage.cpp
    src/database.cpp
    vendor/sqlite3/sqlite3.c
)

add_executable(silo ${SOURCES})

target_include_directories(silo PUBLIC 
    include 
    vendor/sqlite3
)

target_link_libraries(silo pthread dl)
