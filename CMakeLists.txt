cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(SpiderBiteMVP VERSION 0.1 LANGUAGES CXX)

set(_ECLIPSE_VERSION "4.5")

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB SOURCES
 main.cpp
 inc/util/*.h
 inc/util/*.hpp
 inc/view/*.h
 inc/view/*.hpp
 src//util/*.cpp
 src/view/*.cpp)

#to take control which files are used, dont go recursive through
#file(GLOB_RECURSE SOURCES src/*.cpp inc/*.h)

message("Following sources found:")
foreach(a ${SOURCES})
  message("${a}")
endforeach()

###############################################################################
## target definitions #########################################################
###############################################################################

#Generate the shared library from the sources
add_executable(SpiderBiteMVP ${SOURCES})

#Set Debug or Release
set(CMAKE_BUILD_TYPE Debug)

# just for example add some compiler flags
#target_compile_options(SpiderBiteMVP PUBLIC -Wextra)

###############################################################################
## compiler definitions########################################################
###############################################################################

#enable c++11 and set it required
set_property(TARGET SpiderBiteMVP PROPERTY CXX_STANDARD 11)
set_property(TARGET SpiderBiteMVP PROPERTY CXX_STANDARD_REQUIRED ON)

#project(SpiderBiteMVP CXX)
#message("Your C++ compiler supports these C++ features:")
#foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
#  message("${i}")
#endforeach()


###############################################################################
## dependencies ###############################################################
###############################################################################

# GTK+
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
add_definitions(${GTK3_CFLAGS_OTHER})

# BOOST
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.61 EXACT COMPONENTS system regex date_time thread serialization log log_setup REQUIRED)

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

# POCO
# set the POCO paths and libs
set(POCO_PREFIX "/usr/local") # the directory containing "include" and "lib"
set(POCO_INCLUDE_DIR"${POCO_PREFIX}/include")
set(POCO_LIB_DIR "${POCO_PREFIX}/lib")
set(POCO_LIBS
        "${POCO_LIB_DIR}/libPocoNet.so"
        "${POCO_LIB_DIR}/libPocoUtil.so"
        "${POCO_LIB_DIR}/libPocoFoundation.so"
        "${POCO_LIB_DIR}/libPocoJSON.so"
        "${POCO_LIB_DIR}/libPocoMongoDB.so")

#set(Poco_USE_STATIC_LIBS OFF) 
#set(Poco_USE_MULTITHREADED ON)  
#set(Poco_USE_STATIC_RUNTIME OFF) 
#find_package(Poco 1.7.3 EXACT COMPONENTS PocoNet PocoUtil PocoFoundation PocoJSON PocoMongoDB regex date_time log log_setup REQUIRED)

# MONGODAO
set(MONGODAO_LIBRARY_DIRS ${CMAKE_CURRENT_LIST_DIR}/env/mongodao/lib)
set(MONGODAO_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/env/mongodao/inc)

find_library(
    MONGODAO_LIBRARIES
    NAMES MongoDao
    PATHS ${CMAKE_CURRENT_LIST_DIR}/env/mongodao
    PATH_SUFFIXES "lib"
    NO_DEFAULT_PATH
)

# THREADS
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#CURL_INCLUDE_DIRS   		- where to find curl/curl.h, etc.
#CURL_LIBRARIES      		- List of libraries when using curl.
#CURL_FOUND          		- True if curl found.
#CURL_VERSION_STRING 		- the version of curl found (since CMake 2.8.8)
find_package(CURL REQUIRED)
message(STATUS "CURL Version: ${CURL_VERSION_STRING}")

include_directories(${GTK3_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${POCO_INCLUDE} ${MONGODAO_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS} ${Boost_LIBRARIES} ${POCO_LIB_DIR} ${MONGODAO_LIBRARY_DIRS} ${CURL_LIBRARIES})
target_link_libraries(SpiderBiteMVP ${GTK3_LIBRARIES} ${Boost_LIBRARIES} ${POCO_LIBS} Threads::Threads ${MONGODAO_LIBRARIES} ${CURL_LIBRARIES})
