#include "main.hh"

struct camera *cam = (struct camera *)malloc(sizeof(struct camera));
extern std::vector<object> objects;
extern char order[9999];
Shader *model_shader;
GLFWwindow* window;

extern std::vector<std::vector<float>> land;
extern std::vector<std::vector<float>> texture;

bool firstMouse = true;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;


struct unit *me = NULL;

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		printf ("you need 4 arguments: ip, port, name, password");
		return -1;
	}

	
	extern int netfd;
	try_connect(argv[1], argv[2]);
	if (netfd == -1)
	{
		printf ("connection failed\n");
		return -2;
	}
	if (try_login(argv[3], argv[4]) != 0)
	{
		printf ("login failed\n");
		return -3;
	}
	cam->cameraPos   = glm::vec3(0.0f, 0.f, 0.0f);
	cam->cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	cam->cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
	cam->fov   =  45.0f;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment - Weather effects", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_input_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// NEW!
	// build and compile the shader programs
	model_shader = new Shader("cfiles/shaders/shader.vert", "cfiles/shaders/color.frag");

	// NEW!
	// set up the z-buffer
	//glDepthRange(1,-1); // make the NDC a right handed coordinate system, with the camera pointing towards -z
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glEnable(GL_DEPTH_TEST); // turn on z-buffer depth test
	glDepthFunc(GL_LESS); // draws fragments that are closer to the screen in NDC
	send (netfd, "p", 1, 0);
    char rep = 'p';
     while (rep == 'p')
        recv(netfd, &rep, 1,0);
    if (rep == 'n')
    {
        printf ("no character at our name on the map\n");
        return -4;
    }

    init_scene(argv[3]);
	// render loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render the cones
		glUseProgram(model_shader->ID);
		glm::mat4 projection = glm::perspective(glm::radians(cam->fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		model_shader->setMat4("projection", projection);

		glm::mat4 view = glm::lookAt(cam->cameraPos, cam->cameraPos + cam->cameraFront, cam->cameraUp);
		model_shader->setMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//objects[0].ry += 1.0f;
		draw_objects(objects, model);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (order[0] != 0)
		{
			send(netfd, order, strlen(order), MSG_NOSIGNAL);
			order[0] = 0;
		}
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// glfw: called whenever a mouse button is pressed
void button_input_callback(GLFWwindow* window, int button, int action, int mods){
}

// glfw: called whenever a keyboard key is pressed
void key_input_callback(GLFWwindow* window, int button, int other,int action, int mods){
	float speed = 0.5;
	if (button == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		sprintf(order + strlen(order), "%d 07 +%f %d 05 -%f ", me->id, speed * sin(me->obj->ry), me->id, speed * cos(me->obj->ry));
	if (button == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		sprintf(order + strlen(order), "%d 07 -%f %d 05 +%f ", me->id, speed * sin(me->obj->ry), me->id, speed * cos(me->obj->ry));
	if (button == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		sprintf(order + strlen(order), "%d 07 -%f %d 05 +%f ", me->id, speed * cos(me->obj->ry), me->id, speed * sin(me->obj->ry));
	if (button == GLFW_KEY_DOWN && (action == GLFW_REPEAT ||  action == GLFW_PRESS))
		sprintf(order + strlen(order), "%d 07 +%f %d 05 -%f ", me->id, speed * cos(me->obj->ry), me->id, speed * sin(me->obj->ry));
	sprintf(order + strlen(order), "%d 06 %f ", me->id, land[(int)cam->cameraPos.z][(int)cam->cameraPos.x] + 5);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void init_scene(char *name)
{
	char *hcsv = recv_file();
    char *tcsv = recv_file();
	char *l = recv_file();
	generate_land(hcsv, tcsv);
	me = init_unit_list(l, name);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
    float sensitivity = 0.2f; // change this value to your liking


	if (xoffset*xoffset < 2000 and yoffset * yoffset < 2000)
	{	
	    xoffset *= sensitivity;
	    yoffset *= sensitivity;

	    me->obj->ry += xoffset;
	    me->obj->rz += yoffset;
	}

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (me->obj->rz > 89.0f)
        me->obj->rz = 89.0f;
    if (me->obj->rz < -89.0f)
        me->obj->rz = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(me->obj->ry)) * cos(glm::radians(me->obj->rz));
    front.y = sin(glm::radians(me->obj->rz));
    front.z = sin(glm::radians(me->obj->ry)) * cos(glm::radians(me->obj->rz));
    cam->cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam->fov -= (float)yoffset;
	if (cam->fov < 1.0f)
		cam->fov = 1.0f;
	if (cam->fov > 45.0f)
		cam->fov = 45.0f;
}
