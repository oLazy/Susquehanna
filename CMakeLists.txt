cmake_minimum_required(VERSION 3.16)

# -------------------------
# Project setup
# -------------------------
project(Susquehanna LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Stricter warnings (tweak as you like)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion)
elseif (MSVC)
    add_compile_options(/W4 /permissive-)
endif()

# -------------------------
# Folder layout
# -------------------------
set(SRC_DIR   ${CMAKE_SOURCE_DIR}/src)
set(DATA_DIR  ${CMAKE_SOURCE_DIR}/data)
set(UTEST_DIR ${CMAKE_SOURCE_DIR}/utest)

# So all targets can include headers from chapter folders
include_directories(${SRC_DIR})


# -------------------------
# Discover chapter folders and create targets
# - If a chapter contains a main.cpp -> build an executable named after the chapter
# - Otherwise, build a static library named after the chapter
# -------------------------
file(GLOB CHAPTER_DIRS RELATIVE ${SRC_DIR} ${SRC_DIR}/*)

foreach(CH ${CHAPTER_DIRS})
    if (IS_DIRECTORY "${SRC_DIR}/${CH}")
        file(GLOB CH_SOURCES "${SRC_DIR}/${CH}/*.cpp")
        if (CH_SOURCES)
            # Decide if this chapter has a main program
            if (EXISTS "${SRC_DIR}/${CH}/main.cpp")
                # Executable target
                add_executable(${CH} ${CH_SOURCES})
                # Put executables under bin/<chapter>
                set_target_properties(${CH} PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CH}
                )
                # Expose data path to the code (e.g., std::filesystem::path(DATA_DIR))
                target_compile_definitions(${CH} PRIVATE DATA_DIR="${DATA_DIR}")
            else()
                # Library target (no main.cpp present)
                add_library(${CH} STATIC ${CH_SOURCES})
                list(APPEND CHAPTER_LIBS ${CH})
                # Consumers can include chapter headers via src/
                target_include_directories(${CH} PUBLIC ${SRC_DIR})
                target_compile_definitions(${CH} PUBLIC DATA_DIR="${DATA_DIR}")
            endif()
        endif()
    endif()
endforeach()

# -------------------------
# Tests (single runner from utest/*.cpp)
# - Links to all chapter libraries discovered above (if any)
# -------------------------
file(GLOB UTEST_SOURCES "${UTEST_DIR}/*.cpp")
if (UTEST_SOURCES)
    add_executable(utest_runner ${UTEST_SOURCES})
    set_target_properties(utest_runner PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/utest
    )
    target_include_directories(utest_runner PRIVATE ${SRC_DIR})
    if (CHAPTER_LIBS)
        target_link_libraries(utest_runner PRIVATE ${CHAPTER_LIBS})
    endif()
    target_compile_definitions(utest_runner PRIVATE DATA_DIR="${DATA_DIR}")
endif()

# -------------------------
# Optional: CTest integration (you can add tests later with add_test)
# -------------------------
include(CTest)
