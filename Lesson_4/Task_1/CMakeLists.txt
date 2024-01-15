cmake_minimum_required(VERSION 3.22.0)

set(PostgreSQL_ADDITIONAL_VERSIONS "16.1")

project(MyProject)

add_executable(MyProject main.cpp)

add_subdirectory("D:\\1\\libpqxx-7.8.1" libpqxx-build) 

target_compile_features(MyProject PRIVATE cxx_std_17)

target_link_libraries(MyProject PRIVATE pqxx)