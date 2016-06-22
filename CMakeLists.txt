cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(SpiderBite VERSION 0.1 LANGUAGES CXX)

set(_ECLIPSE_VERSION "4.5")

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB SOURCES
 main.cpp
 inc/*.h
 inc/ui/*.h
 src/*.cpp
 src/ui/*.cpp)

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
add_executable(SpiderBite ${SOURCES})

#Set Debug or Release
set(CMAKE_BUILD_TYPE Debug)

# just for example add some compiler flags
#target_compile_options(SpiderBite PUBLIC -Wextra)


###############################################################################
## compiler definitions########################################################
###############################################################################

#enable c++11 and set it required
set_property(TARGET SpiderBite PROPERTY CXX_STANDARD 11)
set_property(TARGET SpiderBite PROPERTY CXX_STANDARD_REQUIRED ON)

#project(SpiderBite CXX)
#message("Your C++ compiler supports these C++ features:")
#foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
#  message("${i}")
#endforeach()


###############################################################################
## dependencies ###############################################################
###############################################################################

# Curl
include(FindCURL)
find_package(CURL REQUIRED)

if (NOT CURL_FOUND)
  message (FATAL_ERROR "Curl is not supported")
endif (NOT CURL_FOUND)

# GTK+
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
add_definitions(${GTK3_CFLAGS_OTHER})

# BOOST
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.61 EXACT COMPONENTS system regex REQUIRED)

# THREADS
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${GTK3_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS} ${Boost_LIBRARIES} ${Curl_LIBRARIES})
target_link_libraries(SpiderBite ${GTK3_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} Threads::Threads)