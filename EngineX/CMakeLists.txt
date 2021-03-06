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
        src/Platform/OpenGL/OpenGLRenderer.cpp
        src/Platform/OpenGL/OpenGLRenderer.h
        src/EngineX/Debug/Profiling/Instrumentor.h
        src/EngineX/Editor/SceneEditor.cpp
        src/EngineX/Editor/SceneEditor.h
        src/EngineX/Core.h
        src/Platform/OpenGL/OpenGLFrameBuffer.cpp
        src/Platform/OpenGL/OpenGLFrameBuffer.h
        src/Platform/OpenGL/OpenGLBuffer.cpp
        src/Platform/OpenGL/OpenGLBuffer.h
        src/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Platform/OpenGL/OpenGLVertexArray.h
        src/Platform/OpenGL/OpenGLShader.cpp
        src/Platform/OpenGL/OpenGLShader.h
        src/EngineX/Scene.cpp
        src/EngineX/Scene.h
        src/EngineX/Mesh.h
        src/EngineX/Vertex.h
        src/EngineX/Camera.h
        src/EngineX/DirectionLight.h src/EngineX/Material.h)


message(STATUS "${PROJECT_NAME} ${CMAKE_CXX_FLAGS}")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")
add_subdirectory(vendor/GLFW)

add_subdirectory(vendor/Glad)
add_subdirectory(vendor/imgui)

#-----assimp setup----------------------------------------------

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_BUILD_TESTS OFF)

set(ASSIMP_NO_EXPORT TRUE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE)

set(ASSIMP_BUILD_FBX_IMPORTER TRUE)

set(ASSIMP_IMPORTERS_ENABLED FBX)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp)

#---------------------------------------------------------------

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/include

        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} glfw Glad ImGui opengl32 assimp)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/expch.h)