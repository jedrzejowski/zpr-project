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
        src/logger.cpp
        src/lib/signal.h
        src/lib/object.h
        src/lib/object.cpp
        src/lib/perlin.h
        src/lib/perlin.cpp)

## engine
target_sources(${APP_TARGET} PUBLIC
        src/opengl.h
        src/engine/exception.h
        src/engine/resources.h
        src/engine/resources.cpp

        src/engine/point.h
        src/engine/point.cpp

        src/engine/texture.h
        src/engine/texture.cpp
        src/engine/light.h
        src/engine/light.cpp
        src/engine/shader.h
        src/engine/shader.cpp
        src/engine/camera.h
        src/engine/camera.cpp

        src/engine/window.h
        src/engine/window.cpp
        src/engine/scene.h
        src/engine/scene.cpp
        src/engine/abs3DObj.cpp
        src/engine/abs3DObj.h

        src/engine/keyboard.h
        src/engine/keyboard.cpp
        src/engine/mouse.h
        src/engine/mouse.cpp
        src/engine/inputInterface.h
        src/engine/inputInterface.cpp

        src/engine/fpsCounter.h
        src/engine/fpsCounter.cpp

        src/engine/Engine.h)


#engine
target_sources(${APP_TARGET} PUBLIC
        src/gui/GUI.h
        src/gui/interface.h
        src/gui/interface.cpp
        src/gui/guiObj.h
        src/gui/guiObj.cpp
        src/gui/button.h
        src/gui/button.cpp)

## block
target_sources(${APP_TARGET} PUBLIC
        src/block/Blocks.h
        src/block/block.h
        src/block/block.cpp
        src/block/solidblock.h
        src/block/solidblock.cpp
        src/block/types/stone.h
        src/block/types/stone.cpp
        src/block/types/dirt.h
        src/block/types/dirt.cpp)

## map
target_sources(${APP_TARGET} PUBLIC
        src/map/Map.h
        src/map/chunk.h
        src/map/chunk.cpp
        src/map/worldmap.h
        src/map/worldmap.cpp
        src/map/renderer.h
        src/map/renderer.cpp
        src/map/chunkRenderer.h
        src/map/chunkRenderer.cpp
        src/map/chunkGenerator.h
        src/map/chunkGenerator.cpp)

## game
target_sources(${APP_TARGET} PUBLIC
        src/game/gameWin.h
        src/game/gameWin.cpp
        src/game/player.h
        src/game/player.cpp
        src/game/gameScene.h
        src/game/gameScene.cpp
        src/game/inGameMenu.h
        src/game/inGameMenu.cpp)

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