cmake_minimum_required(VERSION 3.21)
project(TurnBasedCombatSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add this for MSVC compatibility
if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

# enable dependencies
include(FetchContent)

# fmt library for string formatting
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

#target_link_libraries(combat_core fmt::fmt)

# catch2 library for unit tests
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

# combat core library with all .cpp files
add_library(combat_core
    src/character.cpp
    src/combat_system.cpp
    src/team.cpp
    src/combat_logger.cpp
    )

# include .h files for combat_core
target_include_directories(combat_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# link combat_core to fmt
target_link_libraries(combat_core PRIVATE
    fmt::fmt
)

# main executable (main.cpp)
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# link combat_core to main executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    combat_core # already linked to fmt from before
) 

# tests executable
add_executable(tests
    tests/test_character.cpp
    tests/test_combat_system.cpp
    tests/test_team.cpp
    tests/test_effect.cpp)

# link Catch2 & combat_core to tests executable
target_link_libraries(tests PRIVATE
    Catch2::Catch2WithMain
    combat_core
)

include(CTest)
enable_testing()
add_test(NAME AllTests COMMAND tests)