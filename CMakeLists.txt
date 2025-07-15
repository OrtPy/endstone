cmake_minimum_required(VERSION 3.15)
project(endstone LANGUAGES CXX)

# Endstone requires C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ─── Compiler Check (コメントアウト済み) ─────────────────────────────────────
#if (WIN32)
#    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
#        message(FATAL_ERROR "Endstone: MSVC is required on Windows.")
#    endif ()
#elif (UNIX)
#    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#        message(FATAL_ERROR "Endstone: Clang is required on Linux.")
#    endif ()
#    # Force use libstdc++11 for ABI compatibility (不要になったため削除)
#    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++11 -fPIC" CACHE STRING "" FORCE)
#else ()
#    message(FATAL_ERROR "Endstone: Unsupported platform ${CMAKE_SYSTEM_NAME}.")
#endif ()
# ────────────────────────────────────────────────────────────────────────────────

# Options
option(CODE_COVERAGE "Enable code coverage reporting" OFF)
option(ENDSTONE_ENABLE_DEVTOOLS "Build Endstone with devtools support" OFF)
option(ENDSTONE_SEPARATE_DEBUG_INFO "Separate debug info from binaries" OFF)

# Endstone header-only API
add_subdirectory(include)

# If this is being included as a subdirectory of another project, stop here
if (NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    return()
endif ()

# Implementations
add_subdirectory(third_party)
add_subdirectory(src/endstone/python)
add_subdirectory(src/bedrock)
add_subdirectory(src/endstone/core)
add_subdirectory(src/endstone/runtime)

# Tests
if (NOT BUILD_TESTING STREQUAL "OFF")
    enable_testing()

    if (CODE_COVERAGE AND (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
        # Coverage flags for GCC/Clang
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
    endif ()

    find_package(GTest REQUIRED)
    include(GoogleTest)
    add_subdirectory(tests)
endif ()

