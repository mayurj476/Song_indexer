cmake_minimum_required(VERSION 3.10)

project(indexer VERSION 0.1.0 LANGUAGES C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_RPATH "/usr/local/lib")

# Binary target name
set(BINARY_NAME ${PROJECT_NAME})

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------

find_package(PkgConfig REQUIRED)
pkg_check_modules(TAGLIB REQUIRED taglib>=2.1.1)

# ------------------------------------------------------------------------------
# dbmanager Library
# ------------------------------------------------------------------------------

# Source files for dbmanager shared library
set(DBMANAGER_SRC_FILES
    DbManager/src/DbSelector.cpp
    DbManager/src/DbInserter.cpp
    DbManager/src/DbManager.cpp
)

add_library(dbmanager SHARED ${DBMANAGER_SRC_FILES})

target_include_directories(dbmanager
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DbManager/include
)

target_link_libraries(dbmanager
    PRIVATE
        sqlite3
        pthread
)

# ------------------------------------------------------------------------------
# indexer Executable
# ------------------------------------------------------------------------------

# Source files for main application
set(SRC_FILES
    MetadataParser/src/MetaDataparser.cpp
    main.cpp
)

add_executable(${BINARY_NAME} ${SRC_FILES})

target_include_directories(${BINARY_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/MetadataParser/include
        ${TAGLIB_INCLUDE_DIRS}
)

target_link_libraries(${BINARY_NAME}
    PRIVATE
        dbmanager
        stdc++fs           # May not be needed for C++17, depending on compiler
        ${TAGLIB_LIBRARIES}
        z                  # zlib needed by taglib
)

