cmake_minimum_required(VERSION 3.10.0)
project(indexer VERSION 0.1.0 LANGUAGES C CXX)
set(BINARY_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_RPATH "/usr/local/lib")


set(LIB_SRC_FILES ${SRC_FILES}
    DbManager/src/DbSelector.cpp
    DbManager/src/DbInserter.cpp
    DbManager/src/DbManager.cpp
)

add_library(dbmanager SHARED ${LIB_SRC_FILES})

target_include_directories(dbmanager
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/DbManager/include
)


target_link_libraries(dbmanager
    PRIVATE
    sqlite3
    pthread #thread
)


find_package(PkgConfig)
pkg_check_modules(TAGLIB REQUIRED taglib>=2.1.1)


set(SRC_FILES
    MetadataParser/src/MetaDataparser.cpp
    MetadataParser/src/main.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/MetadataParser/include)

add_executable(${BINARY_NAME} ${SRC_FILES})
 
target_include_directories(${BINARY_NAME}
    PRIVATE 
    ${TAGLIB_INCLUDE_DIRS}    
)
target_link_libraries("${BINARY_NAME}"
    PRIVATE
    dbmanager
    stdc++fs
    ${TAGLIB_LIBRARIES} #taglib library
    z      #added for zlib used in taglib 
    
)