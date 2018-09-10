cmake_minimum_required(VERSION 3.0)

#------------------------------------------------------------------------------
# Project variables

project(dwmstatus)

#------------------------------------------------------------------------------
# Build options

option(DWMSTATUS_WITH_X11 "Build X11 display module." ON)

#------------------------------------------------------------------------------
# Compiler-specific

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-gnu-keywords")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

#------------------------------------------------------------------------------
# Targets

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}
  )

set(DWMSTATUS_SRCS
  config.cpp
  display.cpp
  loadavg.cpp
  main.cpp
  status.cpp
  time.cpp
  )

if(DWMSTATUS_WITH_X11)
  find_package(X11 REQUIRED)
  add_definitions(-DDWMSTATUS_WITH_X11)
  include_directories(${X11_INCLUDE_DIR})
  list(APPEND DWMSTATUS_LIBS ${X11_LIBRARIES})
endif(DWMSTATUS_WITH_X11)

add_executable(dwmstatus ${DWMSTATUS_SRCS})
target_link_libraries(dwmstatus ${DWMSTATUS_LIBS})

#------------------------------------------------------------------------------
# Installation

install(TARGETS dwmstatus DESTINATION bin)
