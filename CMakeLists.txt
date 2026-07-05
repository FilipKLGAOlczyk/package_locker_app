cmake_minimum_required(VERSION 3.10)

set (-Wall -Wpedantic -Wextra -Werror)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#zeby spuchowalo

if(APPLE)
    set(BOOST_ROOT "/opt/homebrew")
endif (APPLE)

# Profil debug i maksymalny poziom debug info g3 oraz format debug info na dwarf-4 (musi być gdb w wersji 7).
# BUILD_TYPE może być ustawiony na:
#empty
#Debug
#Release
#RelWithDebInfo
#MinSizeRel

# Set additional debuf flags for debugger
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")

project(Program)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_subdirectory(library)
add_subdirectory(program)

enable_testing()