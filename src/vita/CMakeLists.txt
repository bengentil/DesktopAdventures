cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

set(SHORT_NAME desktopadv)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "DesktopAdventures")
set(VITA_TITLEID  "DESADV001")

if(DEFINED ENV{NET_DEBUG_HOST} AND DEFINED ENV{NET_DEBUG_PORT} )
  set(NET_DEBUG "-DVITA_NET_DEBUG -DNET_DEBUG_HOST=\\\"$ENV{NET_DEBUG_HOST}\\\" -DNET_DEBUG_PORT=$ENV{NET_DEBUG_PORT}")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=gnu11 -DRENDER_GL -DDAT_IN_RAM ${NET_DEBUG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -DRENDER_GL -DDAT_IN_RAM ${NET_DEBUG}")

include_directories(
  ../include
  .
  ..
)

file(GLOB SOURCES ./*.c ../*.c)

add_executable(${SHORT_NAME}
  ${SOURCES}
)

target_link_libraries(${SHORT_NAME}
  SceDisplay_stub
  SceCtrl_stub
  vitaGL
  c
  SceCommonDialog_stub
  m
  SceGxm_stub
  SceDisplay_stub
  SceCtrlForDriver_stub
  SceCtrl_stub
  SceNet_stub
  SceSysmodule_stub
)

vita_create_self(${SHORT_NAME}.self ${SHORT_NAME})
vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
)
