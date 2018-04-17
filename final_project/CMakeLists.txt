cmake_minimum_required(VERSION 3.9)
project(final_project)

include_directories(

        include
        lib/glfw/include
        lib/glad/include
        lib/glm

)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

add_executable(${PROJECT_NAME} 
	source/main.cpp
	lib/glad/src/glad.c
	include/Background.h
	include/Shader.h
	include/Avatar.h
	include/ScreenObject.h
	include/Obstacle.h
)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})