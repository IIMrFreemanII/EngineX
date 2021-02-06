cmake_minimum_required(VERSION 3.17)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)

#if (${MSVC})
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
#    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /MP")
#endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(
        ${PROJECT_NAME}

        PRIVATE
        ${CMAKE_SOURCE_DIR}/EngineX/vendor/spdlog/include
        ${CMAKE_SOURCE_DIR}/EngineX/vendor/glm
        ${CMAKE_SOURCE_DIR}/EngineX/vendor
        ${CMAKE_SOURCE_DIR}/EngineX/src
)

target_link_libraries(${PROJECT_NAME} EngineX)