cmake_minimum_required(VERSION 2.6)
project(cpp-smb)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(cpp-smb_VERSION_MAJOR 0)
set(cpp-smb_VERSION_MINOR 1)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
 set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
 set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
 if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
   string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
 else()
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
 endif()
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
find_package(LibXml2 2.92.0 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_MIXER_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR})
add_executable(cpp-smb src/main.cpp
  src/entity.cpp
  src/player.cpp
  src/resource_manager.cpp
  src/tile_map.cpp
  src/tile.cpp
  src/scene.cpp
  src/level.cpp
  src/level_data.cpp
  src/main_scene.cpp
  src/viewport.cpp)

target_link_libraries(cpp-smb
  ${SDL2_LIBRARY}
  ${SDL2_IMAGE_LIBRARY}
  ${SDL2_MIXER_LIBRARY}
  ${SDL2_TTF_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${LIBXML2_LIBRARIES})

install(TARGETS cpp-smb RUNTIME DESTINATION ${BIN_DIR})
