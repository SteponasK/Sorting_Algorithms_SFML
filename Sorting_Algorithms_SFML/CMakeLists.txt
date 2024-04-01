# CMakeList.txt : CMake project for CMakeSFMLProject, include source and define
cmake_minimum_required(VERSION 3.8)
project(CMakeSFMLProject)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject "CMakeSFMLProject.cpp" "BubbleSort0824.cpp" "InsertionSort0824.cpp" "ShakerSort0824.cpp" "SelectionSort0824.cpp" "DoubleSelectionSort0824.cpp" "info0824.h" "algorithm0824.h" )
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)
add_custom_command(
    TARGET CMakeSFMLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Resources
            ${CMAKE_CURRENT_BINARY_DIR}/Release)

add_custom_command(
    TARGET CMakeSFMLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Resources
            ${CMAKE_CURRENT_BINARY_DIR}/Debug)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS CMakeSFMLProject)