cmake_minimum_required(VERSION 3.10)
project(Astroids-Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/main.cpp
)

# Find SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)