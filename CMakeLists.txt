cmake_minimum_required(VERSION 3.16...3.18)

project(BMD
VERSION 0.1
DESCRIPTION "Lightweight platform independent utilities with emphasis on C implementations where possible"
LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)
set(BMD_LIB "bmd")

#SET(BUILD_SHARED_LIBS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(coloredmessage)
include(buildtype)


message(STATUS "Beginning build...")
message(STATUS "Building ${PROJECT_NAME} for ${CMAKE_GENERATOR}")
message(STATUS "Cmake prefix: ${CMAKE_PREFIX_PATH}")
message(STATUS "Sys path: ${CMAKE_SYSTEM_PREFIX_PATH}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Could do things like CMAKE_CXX_STANDARD here

  # We want std=c++xx not g++
#  set(CMAKE_C_STANDARD 11)
#  set(CMAKE_CXX_EXTENSIONS OFF)

  # Lets us use folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Enable testing for the main application
  #include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
      message(STATUS "Found Doxygen")
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, cannot build docs")
  endif()
endif()


add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(app_cpp)

# Still learning about Check2 so for now tests are pointless
#if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
#  add_subdirectory(tests)
#endif()