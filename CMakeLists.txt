cmake_minimum_required(VERSION 3.28...4.0.0)
project(TicTacToe)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#SFML_FETCH
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

#MY_SRC
file(GLOB SRC_FILES src/*.cpp)

#EXECUTABLE
add_executable(${PROJECT_NAME} ${SRC_FILES})

#MY_INCLUDE
target_include_directories(${PROJECT_NAME} PRIVATE ./include)

#SFML_INCLUDE
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics) 