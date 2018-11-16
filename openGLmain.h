#ifndef OPENGLMAIN_H
#define OPENGLMAIN_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_loader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"
#include <iostream>
#include "stb_image.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include "path_algorithm.h"

int main_ogl(unsigned int WIDTH, unsigned int HEIGHT, unsigned int ELEMENTS);

#endif