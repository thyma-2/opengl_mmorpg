#include "model.hh"

extern Shader *model_shader; 
std::vector<struct model*> models = {};

unsigned int load_texture(char *path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	    glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		printf ("failed to load texture from file %s\n", path);
	return texture;
}

std::vector<float> load_obj_data(char *path, int size)
{
	std::vector<float> v = {};
    std::vector<float> ret = {};
	std::vector<float> vt = {};
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf ("error the file %s do not exist\n", path);
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (len > 2)
        {
            if (line[0] == 'v' && line[1] == ' ')
            {
                float tmp1, tmp2, tmp3;;
                sscanf(line, "v %f %f %f", &tmp1, &tmp2, &tmp3);
                v.push_back(tmp1*size);
				v.push_back(tmp2*size);
				v.push_back(tmp3*size);
            }
			else if (line[0] == 'v' && line[1] == 't')
			{
				float tmp1, tmp2;
				sscanf(line, "vt %f %f", &tmp1, &tmp2);
				vt.push_back(tmp1);
				vt.push_back(tmp2);
			}
            else if (line[0] == 'f' && line[1] == ' ')
            {
                int nslash = 0; 
                for (int i = 0; line[i] != 0; i++)
                    if (line[i] == '/')
                        nslash++;
                if (nslash == 6)
                {
                    int tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
                    sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &tmp1, &tmp2, &tmp3, &tmp4, &tmp5, &tmp6, &tmp7, &tmp8, &tmp9);
					ret.push_back(v[(tmp1-1)*3]);
					ret.push_back(v[(tmp1-1)*3+1]);
					ret.push_back(v[(tmp1-1)*3+2]);
					ret.push_back(vt[(tmp2-1)*2]);
					ret.push_back(vt[(tmp2-1)*2+1]);
					ret.push_back(v[(tmp4-1)*3]);
                    ret.push_back(v[(tmp4-1)*3+1]);
                    ret.push_back(v[(tmp4-1)*3+2]);
                    ret.push_back(vt[(tmp5-1)*2]);
                    ret.push_back(vt[(tmp5-1)*2+1]);
					ret.push_back(v[(tmp7-1)*3]);
                    ret.push_back(v[(tmp7-1)*3+1]);
                    ret.push_back(v[(tmp7-1)*3+2]);
                    ret.push_back(vt[(tmp8-1)*2]);
                    ret.push_back(vt[(tmp8-1)*2+1]);
                }
                else if (nslash == 8)
				{
					int tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp10, tmp11, tmp12;
                    sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &tmp1, &tmp2, &tmp3, &tmp4, &tmp5, &tmp6, &tmp7, &tmp8, &tmp9, &tmp10, &tmp11, &tmp12);
                    ret.push_back(v[(tmp1-1)*3]);
                    ret.push_back(v[(tmp1-1)*3+1]);
                    ret.push_back(v[(tmp1-1)*3+2]);
                    ret.push_back(vt[(tmp2-1)*2]);
                    ret.push_back(vt[(tmp2-1)*2+1]);
                    ret.push_back(v[(tmp4-1)*3]);
                    ret.push_back(v[(tmp4-1)*3+1]);
                    ret.push_back(v[(tmp4-1)*3+2]);
                    ret.push_back(vt[(tmp5-1)*2]);
                    ret.push_back(vt[(tmp5-1)*2+1]);
                    ret.push_back(v[(tmp7-1)*3]);
                    ret.push_back(v[(tmp7-1)*3+1]);
                    ret.push_back(v[(tmp7-1)*3+2]);
                    ret.push_back(vt[(tmp8-1)*2]);
                    ret.push_back(vt[(tmp8-1)*2+1]);
					ret.push_back(v[(tmp7-1)*3]);
                    ret.push_back(v[(tmp7-1)*3+1]);
                    ret.push_back(v[(tmp7-1)*3+2]);
                    ret.push_back(vt[(tmp8-1)*2]);
                    ret.push_back(vt[(tmp8-1)*2+1]);
					ret.push_back(v[(tmp10-1)*3]);
                    ret.push_back(v[(tmp10-1)*3+1]);
                    ret.push_back(v[(tmp10-1)*3+2]);
                    ret.push_back(vt[(tmp11-1)*2]);
                    ret.push_back(vt[(tmp11-1)*2+1]);
                    ret.push_back(v[(tmp4-1)*3]);
                    ret.push_back(v[(tmp4-1)*3+1]);
                    ret.push_back(v[(tmp4-1)*3+2]);
                    ret.push_back(vt[(tmp5-1)*2]);
                    ret.push_back(vt[(tmp5-1)*2+1]);
                }
            }
        }
    }
    fclose(fp);
    if (line)
        free(line);
	return ret;
}


int load_model_from_obj(char *path, int size)
{
	for (int i = 0; i < models.size(); i++)
	{
		if (strcmp(models[i]->path, path) == 0)
			return i;
	}

	int s = strlen(path);

	struct model *model = (struct model*)malloc(sizeof(struct model*));
	model->path = (char*)calloc(s, 1);
    strcat(model->path, path);

	char *pathimg = (char*)malloc(s);
    strncpy(pathimg, path, s-3);
    strcat(pathimg, "jpg");

	unsigned int texture = load_texture(pathimg);
	model->texture = texture;
	free(pathimg);
	std::vector<float> geometry = load_obj_data(path, size);
	unsigned int geometryVBO, VAO;
	createArrayBuffer(geometry, geometryVBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, geometryVBO);
	int posAttributeLocation = glGetAttribLocation(model_shader->ID, "pos");
    glEnableVertexAttribArray(posAttributeLocation);
    glVertexAttribPointer(posAttributeLocation, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	int bite = glGetAttribLocation(model_shader->ID, "vertexUV");
    glEnableVertexAttribArray(bite);
	glVertexAttribPointer(bite, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // texture coord attribute
	model->VAO = VAO;
	model->vertexCount = geometry.size()/5;
	models.push_back(model);
	return models.size()-1;;
}

void createArrayBuffer(const std::vector<float> &array, unsigned int &VBO){
    // create the VBO on OpenGL and get a handle to it
    glGenBuffers(1, &VBO);
    // bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the content of the VBO (type, size, pointer to start, and how it is used)
    glBufferData(GL_ARRAY_BUFFER, array.size() * sizeof(GLfloat), &array[0], GL_STATIC_DRAW);
}
