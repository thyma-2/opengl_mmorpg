#include "land.hh"

extern std::vector<object> objects;
extern std::vector<struct model*> models;
extern Shader *model_shader;

std::vector<std::vector<float>> land;
std::vector<std::vector<float>> texture;

std::vector<std::vector<float>> csv_to_array(char *csv)
{
	std::vector<std::vector<float>> ret = {};
	int i = 0;
	std::vector<float> tmp = {};
    while (csv[i] != 0)
    {
        tmp.push_back(atoi(csv + i));
        while (csv[i] != ',' and csv[i] != '\n')
        	i++;
        if (csv[i] == '\n')
		{
			ret.push_back(tmp);
			tmp = {};
        }
		i++;
    }
	return ret;
}


void generate_land(void)
{
	add_object(nullptr, -1, 0, 0, 0, 0,0,0);
	float s = 0.5;
	int id = 0;

	char *hcsv = recv_file();
	printf ("[%d]\n", strlen(hcsv));
	char *tcsv = recv_file();
	printf ("[%d]\n", strlen(tcsv));
	land = csv_to_array(hcsv);
	texture = csv_to_array(tcsv);
	int sy = land.size();
	int sx = land[0].size();
	struct surface **land2 = (struct surface**)malloc(sy*sizeof(struct surface*));
	for (int i = 0; i < sy; i++)
		land2[i] = (struct surface*)malloc(sx*sizeof(struct surface));
	
	land2[0][0].y00 = land[0][0];
	land2[0][0].y01 = land[0][0];
	land2[0][0].y11 = land[0][0];
	land2[0][0].y10 = land[0][0];
	for (int i = 1; i < sx; i++)
	{	
		land2[0][i].y00 = land2[0][i - 1].y10;
		land2[0][i].y01 = land2[0][i - 1].y11;
		land2[0][i].y10 = land[0][i];
		land2[0][i].y11 = land[0][i];
	}
	for (int i = 1; i < sy; i++)
	{
		land2[i][0].y00 = land2[i - 1][0].y01;
		land2[i][0].y10 = land2[i - 1][0].y11;
		land2[i][0].y11 = land[i][0];
		land2[i][0].y01 = land[i][0];
		for (int j = 1; j < sx; j++)
		{
			land2[i][j].y00 = land2[i - 1][j].y01;
			land2[i][j].y10 = land2[i - 1][j].y11;
			land2[i][j].y01 = land2[i][j - 1].y11;
			land2[i][j].y11 = land[i][j];
		}
	}


	unsigned int herbe = load_texture("models/land_textures/herbe.jpg");
	unsigned int neige = load_texture("models/land_textures/neige.jpg");
	unsigned int sable = load_texture("models/land_textures/sable.jpg");
	unsigned int eau = load_texture("models/land_textures/eau.jpg");
	
	std::vector<float> herbe_geometry {};
	std::vector<float> neige_geometry {};
	std::vector<float> sable_geometry {};
	std::vector<float> eau_geometry {};

	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx; j++)
		{
			if (texture[i][j] == 0)
				eau_geometry.insert(eau_geometry.end(),{
                    -s + j*2*s, land2[i][j].y00, -s + i*2*s,
                    0,0,
                    -s+ j*2*s, land2[i][j].y01, s+ i*2*s,
                    0,1,
                    s+ j*2*s, land2[i][j].y10,-s+ i*2*s,
                    1,0,
                    s+ j*2*s, land2[i][j].y11,s+ i*2*s,
                    1,1,
                    -s+ j*2*s, land2[i][j].y01, s+ i*2*s,
                    0,1,
                    s+ j*2*s, land2[i][j].y10,-s+ i*2*s,
                    1,0
                });
            else if (texture[i][j] == 1)
				sable_geometry.insert(sable_geometry.end(),{
                    -s + j*2*s, land2[i][j].y00, -s + i*2*s,
                    0,0,
                    -s+ j*2*s, land2[i][j].y01, s+ i*2*s,
                    0,1,
                    s+ j*2*s, land2[i][j].y10,-s+ i*2*s,
                    1,0,
                    s+ j*2*s, land2[i][j].y11,s+ i*2*s,
                    1,1,
                    -s+ j*2*s, land2[i][j].y01, s+ i*2*s,
                    0,1,
                    s+ j*2*s, land2[i][j].y10,-s+ i*2*s,
                    1,0
                });
            else if (texture[i][j] == 2)
				herbe_geometry.insert(herbe_geometry.end(),{
                    -s + j*2*s, land2[i][j].y00, -s + i*2*s,
                    0,0,
                    -s+ j*2*s, land2[i][j].y01, s+ i*2*s,
                    0,1,
                    s+ j*2*s, land2[i][j].y10,-s+ i*2*s,
                    1,0,
                    s+ j*2*s, land2[i][j].y11,s+ i*2*s,
                    1,1,
                    -s+ j*2*s, land2[i][j].y01, s+ i*2*s,
                    0,1,
                    s+ j*2*s, land2[i][j].y10,-s+ i*2*s,
                    1,0
                });			
            else
				neige_geometry.insert(neige_geometry.end(),{
					-s + j*2*s, land2[i][j].y00, -s + i*2*s,
					0,0,			
					-s+ j*2*s, land2[i][j].y01, s+ i*2*s,
					0,1,
					s+ j*2*s, land2[i][j].y10,-s+ i*2*s,
					1,0,
					s+ j*2*s, land2[i][j].y11,s+ i*2*s,
					1,1,
					-s+ j*2*s, land2[i][j].y01, s+ i*2*s,
					0,1,
	                s+ j*2*s, land2[i][j].y10,-s+ i*2*s,
					1,0
				});
		}
		free(land2[i]);
	}
	free(land2);
	texture.clear();
	texture.shrink_to_fit();
	struct model *model = (struct model*)malloc(sizeof(struct model*));
	model->texture = herbe;
	model->path = (char*)calloc(12,1);
    strcat (model->path, "modelherbe");
    unsigned int geometryVBO, VAO;
    createArrayBuffer(herbe_geometry, geometryVBO);
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
    model->VAO = VAO;
    model->vertexCount = herbe_geometry.size()/5;
    models.push_back(model);
    add_object(&objects[0], models.size()-1, 0, 0, 0, 0, 0, 0);
	//
	model = (struct model*)malloc(sizeof(struct model*));
    model->texture = eau;
    model->path = (char*)calloc(12,1);
    strcat (model->path, "modeleau");
    geometryVBO, VAO;
    createArrayBuffer(eau_geometry, geometryVBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, geometryVBO);
    posAttributeLocation = glGetAttribLocation(model_shader->ID, "pos");
    glEnableVertexAttribArray(posAttributeLocation);
    glVertexAttribPointer(posAttributeLocation, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    bite = glGetAttribLocation(model_shader->ID, "vertexUV");
    glEnableVertexAttribArray(bite);
    glVertexAttribPointer(bite, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    model->VAO = VAO;
    model->vertexCount = eau_geometry.size()/5;
    models.push_back(model);
    add_object(&objects[0], models.size()-1, 0, 0, 0, 0, 0, 0);
	//
	model = (struct model*)malloc(sizeof(struct model*));
    model->texture = sable;
    model->path = (char*)calloc(12,1);
    strcat (model->path, "modelsable");
    geometryVBO, VAO;
    createArrayBuffer(sable_geometry, geometryVBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, geometryVBO);
    posAttributeLocation = glGetAttribLocation(model_shader->ID, "pos");
    glEnableVertexAttribArray(posAttributeLocation);
    glVertexAttribPointer(posAttributeLocation, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    bite = glGetAttribLocation(model_shader->ID, "vertexUV");
    glEnableVertexAttribArray(bite);
    glVertexAttribPointer(bite, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    model->VAO = VAO;
    model->vertexCount = sable_geometry.size()/5;
    models.push_back(model);
    add_object(&objects[0], models.size()-1, 0, 0, 0, 0, 0, 0);
	//
	model = (struct model*)malloc(sizeof(struct model*));
    model->texture = neige;
    model->path = (char*)calloc(12,1);
    strcat (model->path, "modelneige");
    geometryVBO, VAO;
    createArrayBuffer(neige_geometry, geometryVBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, geometryVBO);
    posAttributeLocation = glGetAttribLocation(model_shader->ID, "pos");
    glEnableVertexAttribArray(posAttributeLocation);
    glVertexAttribPointer(posAttributeLocation, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    bite = glGetAttribLocation(model_shader->ID, "vertexUV");
    glEnableVertexAttribArray(bite);
    glVertexAttribPointer(bite, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    model->VAO = VAO;
    model->vertexCount = neige_geometry.size()/5;
    models.push_back(model);
    add_object(&objects[0], models.size()-1, 0, 0, 0, 0, 0, 0);
}
