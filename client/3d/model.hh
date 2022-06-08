#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "shader.hh"
#include <glm/gtc/type_ptr.hpp>
#include <tuple>
#include "../image/stb_image.h"

struct model{
	unsigned int VAO, vertexCount, texture, VAO2;
	char *path;
};

int load_model_from_obj(char *path, float size);
unsigned int load_texture(char *path);
void createArrayBuffer(const std::vector<float> &array, unsigned int &VBO);
