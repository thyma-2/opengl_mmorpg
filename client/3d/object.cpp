#include "object.hh"
std::vector<object> objects = {};
std::vector<simple_object> simple_objects = {};
extern Shader *model_shader;
extern std::vector<struct model*> models;

struct object *add_object(struct object *father, int model_indice, float x, float y, float z, float rx, float ry, float rz)
{
	object n{};
	n.sun = {};
	n.rx = rx;
	n.rz = rz;
	n.ry = ry;
	n.position = glm::vec3(x,y,z);
	n.model_indice = model_indice;//load_model_from_obj(path);
	if (father == nullptr)
	{
		objects.push_back(n);
		return &objects[objects.size() - 1];
	}
	father->sun.push_back(n);
	return &father->sun[father->sun.size() - 1];
}

struct simple_object add_simple_object(int model_indice, float x, float y, float z)
{
	simple_object n{};
	n.position = glm::vec3(x,y,z);
	n.model_indice = model_indice;
	simple_objects.push_back(n);
	return simple_objects[simple_objects.size()-1];

}

void draw_objects(std::vector<object> root, glm::mat4 model)
{
	for(auto obj : root)
	{
		glm::mat4 model2 = glm::translate(model, obj.position);
		model2 = glm::rotate(model2, glm::radians(obj.rx), glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::rotate(model2, glm::radians(obj.ry), glm::vec3(0.0f, 1.0f, 0.0f));
		model2 = glm::rotate(model2, glm::radians(obj.rz), glm::vec3(0.0f, 0.0f, 1.0F));
		if (obj.model_indice != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, models[obj.model_indice]->texture);
			model_shader->setMat4("model", model2);
			glBindVertexArray(models[obj.model_indice]->VAO);
			glDrawArrays(GL_TRIANGLES,0, models[obj.model_indice]->vertexCount);
		}
		draw_objects(obj.sun, model2);
	}
}
