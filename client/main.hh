#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <math.h>
#include "3d/shader.hh"
#include <glm/gtc/type_ptr.hpp>
#include "3d/object.hh"
#include "land.hh"
#include "unit.hh"
#include "network/net.h"

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void button_input_callback(GLFWwindow* window, int button, int action, int mods);
void key_input_callback(GLFWwindow* window, int button, int other,int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void createArrayBuffer(const std::vector<float> &array, unsigned int &VBO);
void init_scene(char *name);

struct camera {
	float fov;
	glm::vec3 cameraPos, cameraFront, cameraUp;
};
