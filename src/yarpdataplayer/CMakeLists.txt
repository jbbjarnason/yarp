# Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

if(CREATE_YARPDATAPLAYER)

  include(YarpUseQt5)
  include(YarpOSXUtilities)

  set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

  if(YARP_HAS_OPENCV)
    add_definitions(-DHAS_OPENCV)
    include_directories(${OpenCV_INCLUDE_DIRS})
  else()
    message(STATUS "yarpdataplayer: OpenCV not selected, keep on building...")
  endif()

  if(MSVC)
    include_directories(SYSTEM ${dirent_INCLUDE_DIRS})
  endif()

  set(yarpdataplayer_SRCS src/aboutdlg.cpp
                          src/genericinfodlg.cpp
                          src/loadingwidget.cpp
                          src/main.cpp
                          src/mainwindow.cpp
                          src/utils.cpp
                          src/worker.cpp)


  set(yarpdataplayer_HDRS include/aboutdlg.h
                          include/genericinfodlg.h
                          include/loadingwidget.h
                          include/log.h
                          include/mainwindow.h
                          include/utils.h
                          include/worker.h)

  set(yarpdataplayer_QRC_FILES src/RC/res.qrc)
  set(yarpdataplayer_UI_FILES include/UI/aboutdlg.ui
                              include/UI/genericinfodlg.ui
                              include/UI/loadingwidget.ui
                              include/UI/mainwindow.ui)

  set(yarpdataplayer_THRIFT_FILES yarpdataplayer.thrift)
  if(MSVC)
    set(yarpdataplayer_RC_FILES src/RC/yarpdataplayer_resource.rc)
  endif()

  qt5_add_resources(yarpdataplayer_QRC_GEN_SRCS ${yarpdataplayer_QRC_FILES})
  qt5_wrap_ui(yarpdataplayer_UI_GEN_SRCS ${yarpdataplayer_UI_FILES})

  include(YarpIDL)
  yarp_idl_to_dir(${yarpdataplayer_THRIFT_FILES}
                  ${CMAKE_CURRENT_SOURCE_DIR}/idl_generated_code
                  yarpdataplayer_THRIFT_GEN_SRCS
                  yarpdataplayer_THRIFT_GEN_HDRS
                  yarpdataplayer_THRIFT_INCLUDE_DIRS)

  include_directories(${yarpdataplayer_THRIFT_INCLUDE_DIRS})

  source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
               PREFIX "Source Files"
               FILES ${yarpdataplayer_SRCS})
  source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
               PREFIX "Header Files"
               FILES ${yarpdataplayer_HDRS})
  source_group("Resources Files" FILES ${yarpdataplayer_QRC_FILES}
                                       ${yarpdataplayer_RC_FILES})
  source_group("UI Files" FILES ${yarpdataplayer_UI_FILES})
  source_group("Thrift Files" FILES ${yarpdataplayer_THRIFT_FILES})
  source_group("Generated Files" FILES ${yarpdataplayer_QRC_GEN_SRCS}
                                       ${yarpdataplayer_UI_GEN_SRCS}
                                       ${yarpdataplayer_THRIFT_GEN_SRCS}
                                       ${yarpdataplayer_THRIFT_GEN_HDRS})

  add_executable(yarpdataplayer WIN32 ${yarpdataplayer_SRCS}
                                      ${yarpdataplayer_HDRS}
                                      ${yarpdataplayer_QRC_FILES}
                                      ${yarpdataplayer_QRC_GEN_SRCS}
                                      ${yarpdataplayer_UI_FILES}
                                      ${yarpdataplayer_UI_GEN_SRCS}
                                      ${yarpdataplayer_THRIFT_GEN_SRCS}
                                      ${yarpdataplayer_THRIFT_GEN_HDRS}
                                      ${yarpdataplayer_RC_FILES}
                                      ${yarpdataplayer_THRIFT_FILES})

  target_link_libraries(yarpdataplayer YARP_OS
                                       YARP_init
                                       YARP_sig
                                       Qt5::Widgets)

  if(YARP_HAS_OPENCV)
    target_link_libraries(yarpdataplayer ${OpenCV_LIBRARIES})
  endif()

  install(TARGETS yarpdataplayer COMPONENT utilities DESTINATION ${CMAKE_INSTALL_BINDIR})

  set_property(TARGET yarpdataplayer PROPERTY FOLDER "Graphical User Interfaces")

  yarp_osx_duplicate_and_add_bundle(TARGET yarpdataplayer
                                    INSTALL_COMPONENT utilities
                                    INSTALL_DESTINATION "${CMAKE_INSTALL_BINDIR}")

endif()
