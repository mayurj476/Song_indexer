cmake_minimum_required(VERSION 3.10.0)
project(indexer VERSION 0.1.0 LANGUAGES C CXX)
set(BINARY_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_RPATH "/usr/local/lib")

find_package(PkgConfig)
pkg_check_modules(TAGLIB REQUIRED taglib>=2.1.1)


set(SRC_FILES
    MetadataParser/src/MetaDataparser.cpp
    MetadataParser/src/main.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/MetadataParser/include)




add_executable(${BINARY_NAME} ${SRC_FILES})

# include this to avoid glib not found and undefinced refrence error 
target_include_directories(${BINARY_NAME}
    PRIVATE 
    ${TAGLIB_INCLUDE_DIRS}    
)
target_link_libraries("${BINARY_NAME}"
    PRIVATE
    sqlite3
    stdc++fs
    ${TAGLIB_LIBRARIES} #taglib library
    z      #added for zlib used in taglib 
    pthread #thread
    
)