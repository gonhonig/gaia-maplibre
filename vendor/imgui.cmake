 cmake_minimum_required(VERSION 3.29)
 project(imgui)

 set(CMAKE_CXX_STANDARD 20)

 add_library(imgui STATIC
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imconfig.h
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui.cpp
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui.h
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_demo.cpp
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_draw.cpp
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_internal.h
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_tables.cpp
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_widgets.cpp
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_rectpack.h
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_textedit.h
         ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_truetype.h
 )