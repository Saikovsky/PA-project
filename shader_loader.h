#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


#ifndef OPENGL_TEST_FILE_LOADER_H
#define OPENGL_TEST_FILE_LOADER_H

std::string loadShader(const char *filePath);

unsigned int shaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

#endif //OPENGL_TEST_FILE_LOADER_H
