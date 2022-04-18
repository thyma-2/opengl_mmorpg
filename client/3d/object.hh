#pragma once
#include "model.hh"

struct object{
    unsigned int model_indice;
    glm::vec3 position;
    float rx, ry,rz;
	std::vector<object> sun;
};

struct simple_object{
	glm::vec3 position;
	unsigned int model_indice;
};

struct object *add_object(struct object *father, int model_indice, float x, float y, float z, float rx, float ry, float rz);
struct simple_object add_simple_object(int model_indice, float x, float y, float z);
void draw_objects(std::vector<object> root, glm::mat4 model);
void draw_simple_objects(void);
