
add_executable(${APP_TARGET}
        _classdef.h
        main.cpp
        logger.h
        exception.h
        vars.h
        lib/coord.h
        lib/object.h
        lib/object.cpp
        lib/perlin.h
        lib/perlin.cpp
        lib/fs.h
        lib/fs.cpp
        lib/appSettings.h
        lib/appSettings.cpp
        lib/backWorkerQueue.h
        lib/backWorkerQueue.cpp
        lib/stb_image.h
        lib/json.hpp
        lib/jsonFile.h
        lib/jsonFile.cpp
        lib/cfgpath.h
        mainWin.h
        mainWin.cpp)

## engine
target_sources(${APP_TARGET} PUBLIC
        opengl.h
        engine/resources.h
        engine/resources.cpp

        engine/point.h
        engine/point.cpp

        engine/texture.h
        engine/texture.cpp
        engine/light.h
        engine/light.cpp
        engine/shaderProgram.h
        engine/shaderProgram.cpp
        engine/camera.h
        engine/camera.cpp

        engine/window.h
        engine/window.cpp
        engine/scene.h
        engine/scene.cpp
        engine/abs3Dobj.cpp
        engine/abs3Dobj.h
        engine/sub3Dobj.cpp
        engine/sub3Dobj.h

        engine/inputDevice.h
        engine/inputDevice.cpp
        engine/inputButton.h
        engine/inputButton.cpp
        engine/keyboard.h
        engine/keyboard.cpp
        engine/mouse.h
        engine/mouse.cpp
        engine/inputInterface.h
        engine/inputInterface.cpp

        engine/fpsCounter.h
        engine/fpsCounter.cpp

        engine/Engine.h)


## gui
target_sources(${APP_TARGET} PUBLIC
        gui/GUI.h
        gui/interface.h
        gui/interface.cpp
        gui/interfaceShader.h
        gui/interfaceShader.cpp
        gui/text.h
        gui/text.cpp
        gui/guiObj.h
        gui/guiObj.cpp
        gui/rectangleObj.h
        gui/rectangleObj.cpp
        gui/button.h
        gui/button.cpp)

## block
target_sources(${APP_TARGET} PUBLIC
        block/Blocks.h
        block/block.h
        block/block.cpp
        block/solidblock.h
        block/solidblock.cpp
        block/types/stone.h
        block/types/stone.cpp
        block/types/dirt.h
        block/types/dirt.cpp)

## map
target_sources(${APP_TARGET} PUBLIC
        map/Map.h
        map/chunk.h
        map/chunk.cpp
        map/world.h
        map/world.cpp
        map/worldRenderer.h
        map/worldRenderer.cpp
        map/chunkRenderer.h
        map/chunkRenderer.cpp
        map/chunkGenerator.h
        map/chunkGenerator.cpp
        map/chunkLoader.h
        map/chunkLoader.cpp)

## game
target_sources(${APP_TARGET} PUBLIC
        game/Game.h
        game/player.h
        game/player.cpp
        game/gameScene.h
        game/gameScene.cpp
        game/inGameMenu.h
        game/inGameMenu.cpp
        game/mainGame.h
        game/mainGame.cpp)

## menu
target_sources(${APP_TARGET} PUBLIC
        menu/Menu.h
        menu/welcome.h
        menu/welcome.cpp
        menu/settings.h
        menu/settings.cpp
        menu/worlds.h
        menu/worlds.cpp)

