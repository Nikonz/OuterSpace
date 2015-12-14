cmake_minimum_required(VERSION 3.0)

project(OuterSpace)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/sources/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(headers)

set(SOURCES
  sources/CApp.cpp
  sources/CApp_OnCleanup.cpp
  sources/CApp_OnEvent.cpp
  sources/CApp_OnInit.cpp
  sources/CApp_OnLoop.cpp
  sources/CApp_OnMusic.cpp
  sources/CApp_OnRender.cpp
  sources/CEvent.cpp
  sources/CHighscores.cpp
  sources/CMacros.cpp
  sources/CMenu.cpp
  sources/CMusic.cpp
  sources/CObjects.cpp
  sources/CSurface.cpp)

add_executable(outerspace ${SOURCES})

target_link_libraries(outerspace
  ${SDL2_LIBRARY}
  ${SDL2_TTF_LIBRARIES}
  ${SDLMIXER_LIBRARY})
