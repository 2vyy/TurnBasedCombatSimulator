cmake_minimum_required(VERSION 3.29)
project(TurnBasedCombatSimulator LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# combat core library with all .cpp files
add_library(combat_core
    src/character.cpp
    src/combat_system.cpp
    src/team.cpp
)

# include .h files for combat_core
target_include_directories(combat_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# main executable (main.cpp)
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# link combat_core to main executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    combat_core
)

# catch2 library
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

# tests executable
add_executable(tests
    tests/test_main.cpp
    tests/test_character.cpp
    tests/test_combat_system.cpp
    tests/test_team.cpp
)

# link Catch2 & combat_core to tests executable
target_link_libraries(tests PRIVATE
    Catch2::Catch2WithMain
    combat_core
)

include(CTest)
enable_testing()
add_test(NAME AllTests COMMAND tests)