#pragma once
#include "model.hh"

struct object{
    unsigned int model_indice;
    glm::vec3 position;
    float rx, ry,rz;
	std::vector<struct object*> sun;
};


struct object *add_object(struct object *father, int model_indice, float x, float y, float z, float rx, float ry, float rz);
void free_object_tree(struct object root);
void draw_objects(std::vector<struct object*> root, glm::mat4 model);
void free_object_tree(struct object *root);
