cmake_minimum_required(VERSION 3.20)
project(FinalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# Include the include directory
include_directories(include)

# Add GoogleTest (correct path from root)
add_subdirectory(tests/googletest)

# Add source code as a library
add_library(FruitLib
    src/Fruit.cpp
    src/Player.cpp
    src/Boss.cpp    
)

# Add the test executable
add_executable(runTests
    tests/FruitTest.cpp
)

add_executable(runGame
    src/main.cpp
)

# Link everything
target_link_libraries(runTests FruitLib gtest gtest_main pthread)