#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
unsigned int loadTexture(const char *path);
glm::vec3 getMouseWorld(GLFWwindow* window, glm::mat4 projection, glm::mat4 view, glm::vec4 viewport);

// settings
const unsigned int SCR_WIDTH = 1360;
const unsigned int SCR_HEIGHT = 760;
bool blinn = false;
bool blinnKeyPressed = false;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
GLfloat rotx2 = 5.0f;
GLfloat rotsat = 0.0f;


// transform matrix
int id, state;
glm::mat4 rot;
glm::mat4 translate;
glm::mat4 scale;
glm::vec3 mouseWorldCoord;
float objZ;

int main()
{
	int check = 0;
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ruang Kelas", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// build and compile shaders
	// -------------------------
	//Shader shader("1.advanced_lighting.vs", "1.advanced_lighting.fs");
	Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

	// load models
	// -----------

	Model ourModel1(FileSystem::getPath("resources/objects/a/Leather_chair.obj"));
	Model ourModel2(FileSystem::getPath("resources/objects/metal/Metal Desk.obj"));
	Model ourModel3(FileSystem::getPath("resources/objects/HP_Laptop_High_Poly/Laptop_High-Polay_HP_BI_2_obj.obj"));
	Model ourModel4(FileSystem::getPath("resources/objects/papan/papan.obj"));
	Model ourModel5(FileSystem::getPath("resources/objects/lemari/hehe.obj"));
	Model ourModel6(FileSystem::getPath("resources/objects/kipas/kipas.obj"));
	Model ourModel7(FileSystem::getPath("resources/objects/clock/Clock_obj.obj"));
	Model ourModel8(FileSystem::getPath("resources/objects/rak/rak.obj"));
	Model ourModel9(FileSystem::getPath("resources/objects/window/Window.obj"));
	Model ourModel10(FileSystem::getPath("resources/objects/Indoor Pot Plant 2/indoor plant_02.obj"));
	Model ourModel12(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel13(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel14(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel15(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel16(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel17(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel18(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel19(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel11(FileSystem::getPath("resources/objects/source/girl.obj"));
	//wall/wall.obj notebook/notebook Alienware_18/Alienware 18_obj.obj /woodswing/woodswing/woodswing.obj 
	//woodswing/woodswing/SwingRide.obj Laptop1/Laptop.obj window/Window.obj Indoor Pot Plant 2/indoor plant_02.obj
	//metal/Metal Desk.obj window/Window a/chair a/Model chair/School chair.obj

	// transform
	// ---------
	id = state = 0;
	int state1 = 0, state2 = 0, state3 = 0, state4 = 0, state5 = 0, state6 = 0, state7 = 0, state8 = 0, state9 = 0, state10 = 0, state12 = 0, state13 = 0, state14 = 0, state15 = 0, state16 = 0, state17 = 0, state18 = 0, state19 = 0, state20 = 0;
	float objZ1 = 0.0f, objZ2 = 0.0f, objZ3 = 0.0f, objZ4 = 0.0f, objZ5 = 0.0f, objZ6 = 0.0f, objZ7 = 0.0f, objZ8 = 0.0f, objZ9 = 0.0f, objZ10 = 0.0f, objZ12 = 0.0f, objZ13 = 0.0f, objZ14 = 0.0f, objZ15 = 0.0f, objZ16 = 0.0f, objZ17 = 0.0f, objZ18 = 0.0f, objZ19 = 0.0f, objZ20 = 0.0f;
	glm::mat4 translate1, scale1, rot1;
	glm::mat4 translate2, scale2, rot2;
	glm::mat4 translate3, scale3, rot3;
	glm::mat4 translate4, scale4, rot4;
	glm::mat4 translate5, scale5, rot5;
	glm::mat4 translate6, scale6, rot6;
	glm::mat4 translate7, scale7, rot7;
	glm::mat4 translate8, scale8, rot8;
	glm::mat4 translate9, scale9, rot9;
	glm::mat4 translate10, scale10, rot10;
	glm::mat4 translate11, scale11, rot11, transform;
	glm::mat4 translate12, scale12, rot12;
	glm::mat4 translate13, scale13, rot13;
	glm::mat4 translate14, scale14, rot14;
	glm::mat4 translate15, scale15, rot15;
	glm::mat4 translate16, scale16, rot16;
	glm::mat4 translate17, scale17, rot17;
	glm::mat4 translate18, scale18, rot18;
	glm::mat4 translate19, scale19, rot19;
	glm::mat4 translate20, scale20, rot20;


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float planeVertices[] = {
		// positions            // normals         // texcoords
		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
		10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
	};

	// plane VAO
	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);

	// load textures
	// -------------
	unsigned int floorTexture = loadTexture(FileSystem::getPath("resources/textures/wood.png").c_str());

	// shader configuration
	// --------------------
	//shader.use();
	//shader.setInt("texture1", 0);

	// lighting info
	// -------------
	glm::vec3 lightPos(5.0f, 5.0f, 0.0f);
	glm::vec3 lightPos1(-5.0f, 0.0f, 0.0f);
	glm::vec3 lightPos2(5.0f, 0.0f, 0.0f);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.275f, 0.510f, 0.706f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw objects
		ourShader.use();

		//keys
		if (glfwGetKey(window, GLFW_KEY_0) || id == 0) {
			id = 0;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			processInput(window);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		if (glfwGetKey(window, GLFW_KEY_1)) {
			id = 1;
			state1 = state;
			objZ = objZ1;
			translate = translate1;
			scale = scale1;
			rot = rot1;
			check = 1;
		}
		if (glfwGetKey(window, GLFW_KEY_2)) {
			id = 2;
			state2 = state;
			objZ = objZ2;
			translate = translate2;
			scale = scale2;
			rot = rot2;
			check = 2;
		}
		if (glfwGetKey(window, GLFW_KEY_3)) {
			id = 3;
			state3 = state;
			objZ = objZ3;
			translate = translate3;
			scale = scale3;
			rot = rot3;
			check = 3;
		}
		if (glfwGetKey(window, GLFW_KEY_4)) {
			id = 4;
			state4 = state;
			objZ = objZ4;
			translate = translate4;
			scale = scale4;
			rot = rot4;
			check = 4;
		}
		if (glfwGetKey(window, GLFW_KEY_5)) {
			id = 5;
			state5 = state;
			objZ = objZ5;
			translate = translate5;
			scale = scale5;
			rot = rot5;
			check = 5;
		}
		if (glfwGetKey(window, GLFW_KEY_6)) {
			id = 6;
			state6 = state;
			objZ = objZ6;
			translate = translate6;
			scale = scale6;
			rot = rot6;
			check = 6;
		}
		if (glfwGetKey(window, GLFW_KEY_7)) {
			id = 7;
			state7 = state;
			objZ = objZ7;
			translate = translate7;
			scale = scale7;
			rot = rot7;
			check = 7;
		}
		if (glfwGetKey(window, GLFW_KEY_8)) {
			id = 8;
			state8 = state;
			objZ = objZ8;
			translate = translate8;
			scale = scale8;
			rot = rot8;
			check = 8;
		}
		if (glfwGetKey(window, GLFW_KEY_9)) {
			id = 9;
			state9 = state;
			objZ = objZ9;
			translate = translate9;
			scale = scale9;
			rot = rot9;
			check = 9;
		}
		if (glfwGetKey(window, GLFW_KEY_R)) {
			id = 10;
			state10 = state;
			objZ = objZ10;
			translate = translate10;
			scale = scale10;
			rot = rot10;
			check = 10;
		}
		if (glfwGetKey(window, GLFW_KEY_T)) {
			id = 12;
			state12 = state;
			objZ = objZ12;
			translate = translate12;
			scale = scale12;
			rot = rot12;
			check = 12;
		}
		if (glfwGetKey(window, GLFW_KEY_Y)) {
			id = 13;
			state13 = state;
			objZ = objZ13;
			translate = translate13;
			scale = scale13;
			rot = rot13;
			check = 13;
		}
		if (glfwGetKey(window, GLFW_KEY_U)) {
			id = 14;
			state14 = state;
			objZ = objZ14;
			translate = translate14;
			scale = scale14;
			rot = rot14;
			check = 14;
		}
		if (glfwGetKey(window, GLFW_KEY_I)) {
			id = 15;
			state15 = state;
			objZ = objZ15;
			translate = translate15;
			scale = scale15;
			rot = rot15;
			check = 15;
		}
		if (glfwGetKey(window, GLFW_KEY_O)) {
			id = 16;
			state16 = state;
			objZ = objZ16;
			translate = translate16;
			scale = scale16;
			rot = rot16;
			check = 16;
		}
		if (glfwGetKey(window, GLFW_KEY_P)) {
			id = 17;
			state17 = state;
			objZ = objZ17;
			translate = translate17;
			scale = scale17;
			rot = rot17;
			check = 17;
		}
		if (glfwGetKey(window, GLFW_KEY_F)) {
			id = 18;
			state18 = state;
			objZ = objZ18;
			translate = translate18;
			scale = scale18;
			rot = rot18;
			check = 18;
		}
		if (glfwGetKey(window, GLFW_KEY_G)) {
			id = 19;
			state19 = state;
			objZ = objZ19;
			translate = translate19;
			scale = scale19;
			rot = rot19;
			check = 19;
		}
		if (glfwGetKey(window, GLFW_KEY_H)) {
			id = 20;
			state20 = state;
			objZ = objZ20;
			translate = translate20;
			scale = scale20;
			rot = rot20;
			check = 20;
		}

		if (glfwGetKey(window, GLFW_KEY_K)) {
			id = 11;
			translate = translate11;
			scale = scale11;
			rot = rot11;
		}
		if (glfwGetKey(window, GLFW_KEY_DELETE)) {
			id = 999;
		}

		glm::vec4 viewPort = glm::vec4(0.0f, 0.0f, SCR_WIDTH, SCR_HEIGHT);
		glm::mat4 projection2 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view2 = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection2);
		ourShader.setMat4("view", view2);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		// shader.setMat4("projection", projection);
		// shader.setMat4("view", view);
		// set light uniforms
		ourShader.setVec3("viewPos", camera.Position);
		ourShader.setVec3("lightPos[0]", lightPos);
		ourShader.setVec3("lightPos[1]", lightPos1);
		ourShader.setVec3("lightPos[2]", lightPos2);
		ourShader.setInt("nlight", 3);


		ourShader.setInt("blinn", blinn);

		glm::mat4 mouseProjection;
		// transform
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		if (id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 7 || id == 8 || id == 9 || id == 10 || id == 11 || id == 12 || id == 13 || id == 14 || id == 15 || id == 16 || id == 17 || id == 18 || id == 19 || id == 20) {
			glm::mat4 mouseProjection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 3.0f);
			mouseWorldCoord = getMouseWorld(window, mouseProjection, view, viewPort);
		}

		// FIRST OBJECT
		// render the loaded model
		if (id == 1) {
			translate1 = translate;
			scale1 = scale;
			rot1 = rot;
			objZ1 = objZ;
		}

		glm::mat4 model;
		model = model * translate1 * scale1 * rot1;
		ourShader.setMat4("model", model);
		ourModel1.Draw(ourShader);
		// END FIRST OBJECT
		// SECOND OBJECT

		if (id == 2) {
			translate2 = translate;
			scale2 = scale;
			rot2 = rot;
			objZ2 = objZ;
		}

		glm::mat4 model2;
		model2 = model2 * translate2 * scale2 * rot2;
		ourShader.setMat4("model", model2);
		ourModel2.Draw(ourShader);

		// END SECOND OBJECT
		if (id == 11)
		{
			translate11 = translate;
			scale11 = scale;
			rot11 = rot;
		}
		glm::mat4 model11;
		model11 = glm::rotate(model11, rotx2 + 0.1f, glm::vec3(0.0f, -1.2f, 0.0f));
		model11 = glm::translate(model11, glm::vec3(1.0f, -0.3f, 0.0f));
		//model11 = glm::rotate(model11, rotsat, glm::vec3(0.0f, 0.3f, 0.0f));
		model11 = glm::scale(model11, glm::vec3(0.003f, 0.003f, 0.003f));
		//model2 = rot2 * model2 * translate2 * scale2 ;
		ourShader.setMat4("model", model11);
		ourModel11.Draw(ourShader);
		// THIRD OBJECT

		if (id == 3) {
			translate3 = translate;
			scale3 = scale;
			rot3 = rot;
			objZ3 = objZ;
		}

		glm::mat4 model3;
		model3 = model3 * translate3 * scale3 * rot3;
		ourShader.setMat4("model", model3);
		ourModel3.Draw(ourShader);

		// END THIRD OBJECT
		// FOURTH OBJECT

		if (id == 4) {
			translate4 = translate;
			scale4 = scale;
			rot4 = rot;
			objZ4 = objZ;
		}

		glm::mat4 model4;
		model4 = model4 * translate4 * scale4 * rot4;
		ourShader.setMat4("model", model4);
		ourModel4.Draw(ourShader);
		
		if (id == 5) {
			translate5 = translate;
			scale5 = scale;
			rot5 = rot;
			objZ5 = objZ;
		}

		glm::mat4 model5;
		model5 = model5 * translate5 * scale5 * rot5;
		ourShader.setMat4("model", model5);
		ourModel5.Draw(ourShader);

		if (id == 6) {
			translate6 = translate;
			scale6 = scale;
			rot6 = rot;
			objZ6 = objZ;
		}

		glm::mat4 model6;
		model6 = model6 * translate6 * scale6 * rot6;
		ourShader.setMat4("model", model6);
		ourModel6.Draw(ourShader);
		if (id == 7) {
			translate7 = translate;
			scale7 = scale;
			rot7 = rot;
			objZ7 = objZ;
		}

		glm::mat4 model7;
		model7 = model7 * translate7 * scale7 * rot7;
		ourShader.setMat4("model", model7);
		ourModel7.Draw(ourShader);
		if (id == 8) {
			translate8 = translate;
			scale8 = scale;
			rot8 = rot;
			objZ8 = objZ;
		}

		glm::mat4 model8;
		model8 = model8 * translate8 * scale8 * rot8;
		ourShader.setMat4("model", model8);
		ourModel8.Draw(ourShader);
		if (id == 9) {
			translate9 = translate;
			scale9 = scale;
			rot9 = rot;
			objZ9 = objZ;
		}

		glm::mat4 model9;
		model9 = model9 * translate9 * scale9 * rot9;
		ourShader.setMat4("model", model9);
		ourModel9.Draw(ourShader);
		if (id == 10) {
			translate10 = translate;
			scale10 = scale;
			rot10 = rot;
			objZ10 = objZ;
		}

		glm::mat4 model10;
		model10 = model10 * translate10 * scale10 * rot10;
		ourShader.setMat4("model", model10);
		ourModel10.Draw(ourShader);
		if (id == 12) {
			translate12 = translate;
			scale12 = scale;
			rot12 = rot;
			objZ12 = objZ;
		}

		glm::mat4 model12;
		model12 = model12 * translate12 * scale12 * rot12;
		ourShader.setMat4("model", model12);
		ourModel12.Draw(ourShader);


		if (id == 13) {
			translate13 = translate;
			scale13 = scale;
			rot13 = rot;
			objZ13 = objZ;
		}

		glm::mat4 model13;
		model13 = model13 * translate13 * scale13 * rot13;
		ourShader.setMat4("model", model13);
		ourModel13.Draw(ourShader);
		if (id == 14) {
			translate14 = translate;
			scale14 = scale;
			rot14 = rot;
			objZ14 = objZ;
		}

		glm::mat4 model14;
		model14 = model14 * translate14 * scale14 * rot14;
		ourShader.setMat4("model", model14);
		ourModel14.Draw(ourShader);
		if (id == 15) {
			translate15 = translate;
			scale15 = scale;
			rot15 = rot;
			objZ15 = objZ;
		}

		glm::mat4 model15;
		model15 = model15 * translate15 * scale15 * rot15;
		ourShader.setMat4("model", model15);
		ourModel15.Draw(ourShader);
		if (id == 16) {
			translate16 = translate;
			scale16 = scale;
			rot16 = rot;
			objZ16 = objZ;
		}

		glm::mat4 model16;
		model16 = model16 * translate16 * scale16 * rot16;
		ourShader.setMat4("model", model16);
		ourModel16.Draw(ourShader);
		if (id == 17) {
			translate17 = translate;
			scale17 = scale;
			rot17 = rot;
			objZ17 = objZ;
		}

		glm::mat4 model17;
		model17 = model17 * translate17 * scale17 * rot17;
		ourShader.setMat4("model", model17);
		ourModel17.Draw(ourShader);
		if (id == 18) {
			translate18 = translate;
			scale18 = scale;
			rot18 = rot;
			objZ18 = objZ;
		}

		glm::mat4 model18;
		model18 = model18 * translate18 * scale18 * rot18;
		ourShader.setMat4("model", model18);
		ourModel18.Draw(ourShader);
		if (id == 19) {
			translate19 = translate;
			scale19 = scale;
			rot19 = rot;
			objZ19 = objZ;
		}

		glm::mat4 model19;
		model19 = model19 * translate19 * scale19 * rot19;
		ourShader.setMat4("model", model19);
		ourModel19.Draw(ourShader);
		if (id == 20)
		{
			translate20 = translate;
			scale20 = scale;
			rot20 = rot;
		}

		glm::mat4 model20;
		model20 = model20 * translate20 * scale20 * rot20;
		ourShader.setMat4("model", model20);



		//DELETE
		if (id == 999) {
			if (check == 4)
			{
				scale4 = scale;
				rot4 = rot;
				translate4 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 1)
			{
				scale1 = scale;
				rot1 = rot;
				translate1 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 2)
			{
				scale2 = scale;
				rot2 = rot;
				translate2 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 3)
			{
				scale3 = scale;
				rot3 = rot;
				translate3 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 5)
			{
				scale5 = scale;
				rot5 = rot;
				translate5 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 6)
			{
				scale6 = scale;
				rot6 = rot;
				translate6 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 7)
			{
				scale7 = scale;
				rot7 = rot;
				translate7 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 8)
			{
				scale8 = scale;
				rot8 = rot;
				translate8 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 9)
			{
				scale9 = scale;
				rot9 = rot;
				translate9 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 10)
			{
				scale10 = scale;
				rot10 = rot;
				translate10 = glm::translate(translate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
			}
			else if (check == 12)
			{
				scale12 = scale;
				rot12 = rot;
				translate12 = glm::translate(translate, glm::vec3(1200.0f, 1200.0f, 1200.0f));
			}
			else if (check == 13)
			{
				scale13 = scale;
				rot13 = rot;
				translate13 = glm::translate(translate, glm::vec3(1300.0f, 1300.0f, 1300.0f));
			}
			else if (check == 14)
			{
				scale14 = scale;
				rot14 = rot;
				translate14 = glm::translate(translate, glm::vec3(1400.0f, 1400.0f, 1400.0f));
			}
			else if (check == 15)
			{
				scale15 = scale;
				rot15 = rot;
				translate15 = glm::translate(translate, glm::vec3(1500.0f, 1500.0f, 1500.0f));
			}
			else if (check == 16)
			{
				scale16 = scale;
				rot16 = rot;
				translate16 = glm::translate(translate, glm::vec3(1600.0f, 1600.0f, 1600.0f));
			}
			else if (check == 17)
			{
				scale17 = scale;
				rot17 = rot;
				translate17 = glm::translate(translate, glm::vec3(1700.0f, 1700.0f, 1700.0f));
			}
			else if (check == 18)
			{
				scale18 = scale;
				rot18 = rot;
				translate18 = glm::translate(translate, glm::vec3(1800.0f, 1800.0f, 1800.0f));
			}
			else if (check == 19)
			{
				scale19 = scale;
				rot19 = rot;
				translate19 = glm::translate(translate, glm::vec3(1900.0f, 1900.0f, 1900.0f));
			}
			else if (check == 20)
			{
				scale20 = scale;
				rot20 = rot;
				translate20 = glm::translate(translate, glm::vec3(2000.0f, 2000.0f, 2000.0f));
			}

		}

		// floor
		glBindVertexArray(planeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		rotx2 += 0.01;
		rotsat += 0.01;

		std::cout << (blinn ? "Blinn-Phong" : "Phong") << std::endl;

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &planeVAO);
	glDeleteBuffers(1, &planeVBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !blinnKeyPressed)
	{
		blinn = !blinn;
		blinnKeyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE)
	{
		blinnKeyPressed = false;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (id == 0) {
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

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	else {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {

			translate[3].x = mouseWorldCoord.x + camera.Position.x;
			translate[3].y = mouseWorldCoord.y + camera.Position.y;
			translate[3].z = mouseWorldCoord.z + camera.Position.z;
			//translate = glm::translate(translate, glm::vec3(mouseWorldCoord.x, mouseWorldCoord.y, 0.0f));

		}
	}
}

// get mouse world coordinates
// ---------------------------
glm::vec3 getMouseWorld(GLFWwindow* window, glm::mat4 mouseProjection, glm::mat4 view, glm::vec4 viewPort) {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	glm::vec3 screenFar = glm::vec3(x, SCR_HEIGHT - y - 1, -1.0f);
	glm::vec3 screenNear = glm::vec3(x, SCR_HEIGHT - y - 1, 1.0f);
	glm::vec3 worldFar = glm::unProject(screenFar, view, mouseProjection, viewPort);
	glm::vec3 worldNear = glm::unProject(screenNear, view, mouseProjection, viewPort);
	glm::vec3 worldFinal = worldNear - worldFar;

	return worldFinal;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset == 1)
		scale = glm::scale(scale, glm::vec3(1.2f));
	if (yoffset == -1)
		scale = glm::scale(scale, glm::vec3(0.8f));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (id != 0) {
		if (glfwGetKey(window, GLFW_KEY_UP))
			rot = glm::rotate(rot, -0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_DOWN))
			rot = glm::rotate(rot, 0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_LEFT))
			rot = glm::rotate(rot, -0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_RIGHT))
			rot = glm::rotate(rot, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

