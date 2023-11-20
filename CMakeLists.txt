cmake_minimum_required(VERSION 3.5)

project(solarsystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solarsystem main.cpp
    renderer.h renderer.cpp
    vertexarray.h vertexarray.cpp
    vertexbuffer.h vertexbuffer.cpp
    shader.h shader.cpp
    object.h object.cpp
    uvbuffer.h uvbuffer.cpp
    texture.h texture.cpp
    stb_image/stb_image.h stb_image/stb_image.cpp
    fpscontrols.h fpscontrols.cpp
    navigationcontrols.h navigationcontrols.cpp
    camera.h camera.cpp
    controls.h controls.cpp pointlight.h pointlight.cpp userinterface.h userinterface.cpp imgui/imconfig.h imgui/imgui.h imgui/imgui.cpp
    imgui/imgui_demo.cpp imgui/imgui_draw.cpp
    imgui/imgui_internal.h imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp imgui/imstb_rectpack.h
    imgui/imstb_textedit.h imgui/imstb_truetype.h
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_glfw.h
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_opengl3.h
    imgui/backends/imgui_impl_opengl3_loader.h)

target_link_libraries(solarsystem glfw GLEW libGLEW.so libGLU.so libGL.so )
