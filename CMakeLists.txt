cmake_minimum_required(VERSION 3.14)

#------------------------------------------------------------------------------
# Project variables

project(dwmstatus VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#------------------------------------------------------------------------------
# Build options

option(DWMSTATUS_WITH_X11 "Build X11 display module." ON)
option(DWMSTATUS_WITH_UTIME "Build localized time module." ON)
option(DWMSTATUS_WITH_COLOR "Build with ANSI colors in output." ON)
option(DWMSTATUS_WITH_ICONS "Enable icons in status strings." ON)

#------------------------------------------------------------------------------
# Targets

add_executable(dwmstatus
  ${CMAKE_SYSTEM_NAME}/battery.cpp
  ${CMAKE_SYSTEM_NAME}/cputemp.cpp
  blocks.cpp
  display.cpp
  file.cpp
  loadavg.cpp
  maildir.cpp
  main.cpp
  status.cpp
  time.cpp
  )
target_include_directories(dwmstatus
  PRIVATE
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/${CMAKE_SYSTEM_NAME}
  )

if(DWMSTATUS_WITH_X11)
  find_package(X11 REQUIRED)
  target_compile_definitions(dwmstatus PRIVATE -DDWMSTATUS_WITH_X11)
  target_link_libraries(dwmstatus PRIVATE X11::X11)
endif(DWMSTATUS_WITH_X11)

if(DWMSTATUS_WITH_UTIME)
  find_package(ICU REQUIRED COMPONENTS i18n uc)
  target_compile_definitions(dwmstatus PRIVATE -DDWMSTATUS_WITH_UTIME)
  target_link_libraries(dwmstatus PRIVATE ICU::i18n ICU::uc)
  target_sources(dwmstatus PRIVATE utime.cpp)
endif(DWMSTATUS_WITH_UTIME)

if(DWMSTATUS_WITH_COLOR)
  target_compile_definitions(dwmstatus PRIVATE -DDWMSTATUS_WITH_COLOR)
endif(DWMSTATUS_WITH_COLOR)

if(DWMSTATUS_WITH_ICONS)
  target_compile_definitions(dwmstatus PRIVATE -DDWMSTATUS_WITH_ICONS)
endif(DWMSTATUS_WITH_ICONS)

#------------------------------------------------------------------------------
# Installation

install(TARGETS dwmstatus DESTINATION bin)
