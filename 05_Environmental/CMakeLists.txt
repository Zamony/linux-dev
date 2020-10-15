cmake_minimum_required(VERSION 3.1)

project(winregex)

find_library(CURSES_LIBRARY ncursesw)
find_library(PCRE_LIBRARY pcre2-8)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

option(WITHOUT_UTF "Disable UTF support" OFF)

if(WITHOUT_UTF)
  add_definitions(-DREGEX_USE_UTF=0)
else()
  add_definitions(-DREGEX_USE_UTF=1)
endif()

add_executable(winregex regex.c window.c)

target_link_libraries(winregex ${CURSES_LIBRARY} ${PCRE_LIBRARY})