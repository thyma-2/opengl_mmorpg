#include "object.hh"
std::vector<struct object*> objects = {};
extern Shader *model_shader;
extern std::vector<struct model*> models;

void free_object_tree(struct object *root)
{
	for(auto sun : root->sun)
		free_object_tree(sun);
	delete(root);
}

struct object *add_object(struct object *father, int model_indice, float x, float y, float z, float rx, float ry, float rz)
{
	struct object *n = new object();
	n->sun = {};
	n->rx = rx;
	n->rz = rz;
	n->ry = ry;
	n->position = glm::vec3(x,y,z);
	n->model_indice = model_indice;//load_model_from_obj(path);
	if (father == NULL)
	{
		objects.push_back(n);
		return n;
	}
	(father->sun).push_back(n);
	return n;
}

void draw_objects(std::vector<struct object*> root, glm::mat4 model)
{
	for(auto obj : root)
	{
		glm::mat4 model2 = glm::translate(model, obj->position);
		model2 = glm::rotate(model2, glm::radians(obj->rx), glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::rotate(model2, glm::radians(obj->ry), glm::vec3(0.0f, 1.0f, 0.0f));
		model2 = glm::rotate(model2, glm::radians(obj->rz), glm::vec3(0.0f, 0.0f, 1.0F));
		if (obj->model_indice != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, models[obj->model_indice]->texture);
			model_shader->setMat4("model", model2);
			glBindVertexArray(models[obj->model_indice]->VAO);
			glDrawArrays(GL_TRIANGLES,0, models[obj->model_indice]->vertexCount);
		}
		draw_objects(obj->sun, model2);
	}
}
