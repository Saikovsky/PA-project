cmake_minimum_required(VERSION 3.10)
project(projekt_pa_rs)

set(CMAKE_CXX_STANDARD 17)

add_executable(projekt_pa_rs main.cpp winUI.h winUI.cpp shader_loader.h shader_loader.cpp openGLmain.cpp openGLmain.h winControl.cpp winControl.h fragment.frag shader.vert
        stb_image.cpp stb_image.h glm/glm.hpp glm/gtc/matrix_transform.hpp glm/gtc/type_ptr.hpp dijkstra_algorithm.cpp dijkstra_algorithm.h)

# glad
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
#glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.2.1)
target_link_libraries(projekt_pa_rs glfw)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR}/include)
target_link_libraries(projekt_pa_rs ${OPENGL_gl_LIBRARY})