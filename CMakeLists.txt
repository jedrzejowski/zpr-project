cmake_minimum_required(VERSION 3.10)
project(zpr_project)
find_package(PkgConfig)

set(APP_TARGET zpr_app)
set(TEST_TARGET test)

set(CMAKE_CXX_STANDARD 17)

# Biblioteki

## wątki
find_package(Threads REQUIRED)

## boost
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
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
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${EXTRA_LIBS})

# Główny projekt

include_directories(${PROJECT_SOURCE_DIR})


# Pliki projetku
include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/*.cc"
        "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE TEST_FILES
        "${PROJECT_SOURCE_DIR}/src/*.test.cc"
        "${PROJECT_SOURCE_DIR}/src/*.test.cpp")
file(GLOB_RECURSE HEADER_FILES
        "${PROJECT_SOURCE_DIR}/src/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.hpp")
get_filename_component(main_cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ABSOLUTE)

list(REMOVE_ITEM SOURCE_FILES ${TEST_FILES} ${main_cpp})

add_executable(${APP_TARGET} ${HEADER_FILES} ${SOURCE_FILES} ${main_cpp} )
add_executable(${TEST_TARGET} ${HEADER_FILES} ${SOURCE_FILES} ${TEST_FILES})

target_link_libraries(${APP_TARGET} ${LIBRARIES})
target_link_libraries(${TEST_TARGET} ${LIBRARIES})

target_compile_definitions(${TEST_TARGET} PUBLIC TEST)

# Pliki (obrazy/szejdery/itp)
file(COPY res/ DESTINATION res)
