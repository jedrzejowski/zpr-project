cmake_minimum_required(VERSION 3.10)
project(zpr_project)
find_package(PkgConfig)

set(APP_TARGET zpr_app)
set(TEST_TARGET zpr_test)

set(CMAKE_CXX_STANDARD 17)


# Biblioteki

## wątki
find_package(Threads REQUIRED)

## boost
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${BOOST_INCLUDE_DIR})
link_libraries(${Boost_LIBRARIES})

## glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

## opengl
set(OpenGL_GL_PREFERENCE GLVND)
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

set(LIBRARIES
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${EXTRA_LIBS})

# Główny projekt

include_directories(${PROJECT_SOURCE_DIR})



# Pliki projetku
include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE CPP_FILES
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.cc")
file(GLOB_RECURSE HEADER_FILES
        "${PROJECT_SOURCE_DIR}/src/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.h")

add_executable(${APP_TARGET}
        ${HEADER_FILES} ${CPP_FILES})

file(COPY res/ DESTINATION res)

target_link_libraries(${APP_TARGET} ${LIBRARIES})


# Inne pliki