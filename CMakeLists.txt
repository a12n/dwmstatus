cmake_minimum_required(VERSION 3.0)

include(FindPkgConfig)

#------------------------------------------------------------------------------
# Project variables

project(dwmstatus)

set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD 17)

#------------------------------------------------------------------------------
# Build options

option(DWMSTATUS_WITH_X11 "Build X11 display module." ON)
option(DWMSTATUS_WITH_UTIME "Build localized time module." ON)

#------------------------------------------------------------------------------
# Targets

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}
  )

set(DWMSTATUS_SRCS
  ${CMAKE_SYSTEM_NAME}/battery.cpp
  ${CMAKE_SYSTEM_NAME}/cputemp.cpp
  config.cpp
  display.cpp
  loadavg.cpp
  maildir.cpp
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

if(DWMSTATUS_WITH_UTIME)
  pkg_check_modules(ICU REQUIRED icu-i18n)
  add_definitions(-DDWMSTATUS_WITH_UTIME)
  include_directories(${ICU_INCLUDE_DIRS})
  list(APPEND DWMSTATUS_LIBS ${ICU_LIBRARIES})
  list(APPEND DWMSTATUS_SRCS utime.cpp)
endif(DWMSTATUS_WITH_UTIME)

add_executable(dwmstatus ${DWMSTATUS_SRCS})
target_link_libraries(dwmstatus ${DWMSTATUS_LIBS})

#------------------------------------------------------------------------------
# Installation

install(TARGETS dwmstatus DESTINATION bin)
