cmake_minimum_required(VERSION 3.15)
project(zpr_project)
find_package(PkgConfig)

set(APP_TARGET zpr_app)

set(CMAKE_CXX_STANDARD 17)


# Główny projekt

include_directories(${PROJECT_SOURCE_DIR})
add_executable(${APP_TARGET}
        src/_classdef.h
        src/main.cpp
        src/logger.h
        src/logger.cpp)

#engine
target_sources(${APP_TARGET} PUBLIC
        src/engine/exception.h
        src/engine/Resources.h
        src/engine/Resources.cpp

        src/engine/Point3D.h
        src/engine/Point3D.cpp

        src/engine/Texture.h
        src/engine/Texture.cpp
        src/engine/Light.h
        src/engine/Light.cpp
        src/engine/Shader.h
        src/engine/Shader.cpp
        src/engine/Camera.h
        src/engine/Camera.cpp

        src/engine/Window.h
        src/engine/Window.cpp
        src/engine/Scene.h
        src/engine/Scene.cpp
        src/engine/Abs3DObj.cpp
        src/engine/Abs3DObj.h

        src/engine/Engine.h)

## block
target_sources(${APP_TARGET} PUBLIC
        src/block/Blocks.h
        src/block/block.h
        src/block/block.cpp
        src/block/solidblock.h
        src/block/solidblock.cpp
        src/block/types/stone.h
        src/block/types/stone.cpp)

## map
target_sources(${APP_TARGET} PUBLIC
        src/map/Map.h
        src/map/chunk.h
        src/map/chunk.cpp
        src/map/worldmap.h
        src/map/worldmap.cpp
        src/map/renderer.h
        src/map/renderer.cpp
        src/map/chunkrenderer.h
        src/map/chunkrenderer.cpp)

## game
target_sources(${APP_TARGET} PUBLIC
        src/game/gamewin.h
        src/game/gamewin.cpp
        src/game/player.h
        src/game/player.cpp
        src/game/gamescene.h
        src/game/gamescene.cpp)

### inne
#target_sources(${APP_TARGET} PUBLIC
#        src/lib/cord.h
#        src/lib/cord.cpp)

# Biblioteki

## stb
target_sources(${APP_TARGET} PUBLIC
        src/lib/stb_image.h)

## glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

## opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARY_DIRS})

## glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARY_DIRS})

## glm
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_libraries(${GLM_LIBRARY_DIRS})


target_link_libraries(
        ${APP_TARGET}
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${EXTRA_LIBS}
)