# CMake configuration for tests directory

# Output test executables to this directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Download Catch2 single-header if not present
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp")
    file(DOWNLOAD https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp
        SHOW_PROGRESS)
endif()

add_executable(test_barneshut test_barneshut.cpp)
target_include_directories(test_barneshut PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src/barneshut ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_barneshut PRIVATE)
