cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

# MSVC: 支持 UTF-8 源文件编码（中文注释）
add_compile_options(/utf-8)

# ============ 源文件 ============
set(SOURCES
    # Core
    OpenGL/src/main.cpp
    OpenGL/src/Core/Application.cpp
    # Renderer
    OpenGL/src/Renderer/AlphaPass.cpp
    OpenGL/src/Renderer/LightPass.cpp
    OpenGL/src/Renderer/ModelPass.cpp
    OpenGL/src/Renderer/Renderer.cpp
    OpenGL/src/Renderer/StencilPass.cpp
    # Resource
    OpenGL/src/Resource/GeometryFactory.cpp
    OpenGL/src/Resource/Mesh.cpp
    OpenGL/src/Resource/Model.cpp
    OpenGL/src/Resource/RenderTarget.cpp
    OpenGL/src/Resource/Shader.cpp
    OpenGL/src/Resource/Texture.cpp
    OpenGL/src/Resource/VertexArray.cpp
    # Scene
    OpenGL/src/Scene/Scene.cpp
    # UI
    OpenGL/src/UI/DebugUI.cpp
    # Util
    OpenGL/src/Util/PathManager.cpp
    # Dependencies
    OpenGL/vendor/glad/glad.c
    OpenGL/vendor/stb_image/stb_image.cpp
    OpenGL/vendor/imgui/imgui.cpp
    OpenGL/vendor/imgui/imgui_demo.cpp
    OpenGL/vendor/imgui/imgui_draw.cpp
    OpenGL/vendor/imgui/imgui_impl_glfw.cpp
    OpenGL/vendor/imgui/imgui_impl_opengl3.cpp
    OpenGL/vendor/imgui/imgui_tables.cpp
    OpenGL/vendor/imgui/imgui_widgets.cpp
)

# ============ 头文件目录 ============
include_directories(
    ${CMAKE_SOURCE_DIR}/OpenGL
    ${CMAKE_SOURCE_DIR}/OpenGL/src
    ${CMAKE_SOURCE_DIR}/OpenGL/vendor/imgui
    ${CMAKE_SOURCE_DIR}/OpenGL/vendor/stb_image
    ${CMAKE_SOURCE_DIR}/Dependencies
    ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include
    ${CMAKE_SOURCE_DIR}/Dependencies/GLAD/include
    ${CMAKE_SOURCE_DIR}/Dependencies/assimp/include
)

# ============ 可执行文件 ============
add_executable(LearnOpenGL ${SOURCES})

# ============ 链接库 ============
if(MSVC)
    # MSVC 工具链 — 使用预编译的 lib
    target_link_libraries(LearnOpenGL
        ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib-vc2022/glfw3.lib
        ${CMAKE_SOURCE_DIR}/Dependencies/assimp/lib/assimp-vc143-mt.lib
        opengl32
        User32
        Gdi32
        Shell32
    )
    # 复制 assimp DLL 到输出目录
    add_custom_command(TARGET LearnOpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Dependencies/assimp/lib/assimp-vc143-mt.dll
        $<TARGET_FILE_DIR:LearnOpenGL>
    )
else()
    # MinGW / GCC 工具链 — 需要自行编译 GLFW 和 Assimp
    message(WARNING "非 MSVC 工具链需要自行编译 GLFW 和 Assimp 库")
    find_package(glfw3 REQUIRED)
    find_package(assimp REQUIRED)
    target_link_libraries(LearnOpenGL
        glfw
        assimp::assimp
        opengl32
    )
endif()

# ============ 调试工作目录 ============
# 让程序运行时从 OpenGL/ 目录启动（GLSL、Texture 等相对路径依赖于此）
set_property(TARGET LearnOpenGL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/OpenGL")