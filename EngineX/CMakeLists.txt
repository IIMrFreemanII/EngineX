cmake_minimum_required(VERSION 3.17)
project(EngineX)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        src/EngineX.h
        src/exconfig.h
        src/expch.h
        vendor/stb_image/stb_image.cpp
        vendor/stb_image/stb_image.h
        src/EngineX/Application.cpp
        src/EngineX/Application.h
        src/EngineX/Window.h
        src/EngineX/Window.cpp
        src/Platform/OpenGL/OpenGLContext.cpp
        src/Platform/OpenGL/OpenGLContext.h
        src/EngineX/Log.cpp
        src/EngineX/Log.h
        src/EngineX/Renderer/GraphicsContext.h
        src/EngineX/ImGui/ImGuiBuild.cpp
        src/EngineX/Editor/Editor.cpp
        src/EngineX/Editor/Editor.h
        src/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Platform/OpenGL/OpenGLRendererAPI.h
        src/Platform/OpenGL/OpenGLRenderer.cpp
        src/Platform/OpenGL/OpenGLRenderer.h
        src/EngineX/Debug/Profiling/Instrumentor.h
        src/EngineX/Editor/SceneEditor.cpp
        src/EngineX/Editor/SceneEditor.h
        src/EngineX/Core.h
        src/Platform/OpenGL/OpenGLFrameBuffer.cpp src/Platform/OpenGL/OpenGLFrameBuffer.h)

if (${MSVC})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

message(STATUS "${PROJECT_NAME} ${CMAKE_CXX_FLAGS}")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")
add_subdirectory(vendor/GLFW)

add_subdirectory(vendor/GLAD)
add_subdirectory(vendor/imgui)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image

        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} glfw Glad ImGui opengl32)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/expch.h)