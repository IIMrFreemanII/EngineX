cmake_minimum_required(VERSION 3.17)
project(EngineX)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        src/EngineX.h
        vendor/stb_image/stb_image.cpp
        vendor/stb_image/stb_image.h
        src/EngineX/Application.cpp
        src/EngineX/Application.h
        src/EngineX/Window.h
        src/EngineX/Window.cpp
        src/Platform/OpenGL/OpenGLContext.cpp src/Platform/OpenGL/OpenGLContext.h src/EngineX/Log.cpp src/EngineX/Log.h src/EngineX/Renderer/GraphicsContext.h)

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