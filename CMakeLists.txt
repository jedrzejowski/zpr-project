cmake_minimum_required(VERSION 3.15)
project(zpr_project)
find_package(PkgConfig)

set(APP_TARGET zpr_app)

set(CMAKE_CXX_STANDARD 17)


# Główny projekt

include_directories(${PROJECT_SOURCE_DIR})
add_executable(${APP_TARGET} src/main.cpp)

#gengine
target_sources(${APP_TARGET} PUBLIC
        src/gengine/exception.h
        src/gengine/Resources.h
        src/gengine/Resources.cpp

        src/gengine/Point3D.h
        src/gengine/Point3D.cpp

        src/gengine/Texture.h
        src/gengine/Texture.cpp
        src/gengine/Light.h
        src/gengine/Light.cpp
        src/gengine/Shader.h
        src/gengine/Shader.cpp
        src/gengine/Camera.h
        src/gengine/Camera.cpp

        src/gengine/Window.h
        src/gengine/Window.cpp
        src/gengine/Animation.h
        src/gengine/Animation.cpp
        src/gengine/Abs3DObj.cpp
        src/gengine/Abs3DObj.h

        src/gengine/gEngine.h)

# Biblioteki

## glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

## opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

## glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

## glm
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_libraries(${GLM_LIBRARY_DIRS})


target_link_libraries(
        ${APP_TARGET}
        ${GLFW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${EXTRA_LIBS}
)