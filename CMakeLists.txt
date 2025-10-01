cmake_minimum_required(VERSION 3.10)
project(json_cpp)

set(CMAKE_CXX_STANDARD 17)

# Export compile commands for clang-tidy (Linux/Mac only, avoids Windows symlink issues)
if(UNIX)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/obj)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

# Fetch doctest
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)
FetchContent_MakeAvailable(doctest)

# List parser source files
set(PARSER_SOURCES
    src/lib/parsers/array.cpp
    src/lib/parsers/number.cpp
    src/lib/parsers/object.cpp
    src/lib/parsers/pair.cpp
    src/lib/parsers/string.cpp
    src/lib/parsers/value.cpp
)

add_library(json_parsers STATIC ${PARSER_SOURCES})
target_include_directories(json_parsers PUBLIC src/lib/parsers)

# List CLI source files
set(CLI_SOURCES
    src/cli/main.cpp
)

add_executable(cli ${CLI_SOURCES})
target_link_libraries(cli PRIVATE json_parsers)
target_include_directories(cli PRIVATE src/lib/parsers)

# Compiler-specific flags (optional, safe defaults)
if(MSVC)
    target_compile_options(cli PRIVATE /EHsc)
endif()

# Doctest integration: add all test sources in tests/
file(GLOB TEST_SOURCES tests/*.cpp tests/lib/parsers/*.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE json_parsers doctest::doctest)
target_include_directories(tests PRIVATE src/lib/parsers)
enable_testing()
add_test(NAME doctest COMMAND tests)
