#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
void mouse_callback(GLFWwindow* window, double xpos, double ypos); //koordinat
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); //fungsi scrrol buat zoom benda kurangin y
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); //awsd
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

float X1 = 0.0f;
float Y1 = 0.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// transform matrix
glm::mat4 rot;
glm::mat4 translate;
glm::mat4 scale;

int main()
{
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

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

	// build and compile shaders
	// -------------------------
	Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

	// load models
	Model ourModel1(FileSystem::getPath("resources/objects/chair/School chair.obj"));
	Model ourModel2(FileSystem::getPath("resources/objects/notebook/notebook.obj"));
	Model ourModel3(FileSystem::getPath("resources/objects/window/Window.obj"));
	Model ourModel4(FileSystem::getPath("resources/objects/papan/papan.obj"));
	Model ourModel5(FileSystem::getPath("resources/objects/rak/rak.obj"));
	Model ourModel6(FileSystem::getPath("resources/objects/kipas/kipas.obj"));
	Model ourModel7(FileSystem::getPath("resources/objects/clock/clock.obj"));

	// transform
	// ---------
	int id = 0;
	int check = 0;
	glm::mat4 translate1, scale1, rot1;
	glm::mat4 translate2, scale2, rot2;
	glm::mat4 translate3, scale3, rot3;
	glm::mat4 translate4, scale4, rot4;
	glm::mat4 translate5, scale5, rot5;
	glm::mat4 translate6, scale6, rot6;
	glm::mat4 translate7, scale7, rot7;
	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------

	while (!glfwWindowShouldClose(window))
	{

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// render
		// ------
		glClearColor(1.0f, 0.078f, 0.576f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader b/efore setting uniforms
		ourShader.use();

		//PROSES PEMILIHAN OBJECT
		if (glfwGetKey(window, GLFW_KEY_1)) {
			id = 1;
			translate = translate1;
			scale = scale1;
			rot = rot1;
			check = 1;
		}
		if (glfwGetKey(window, GLFW_KEY_2)) {
			id = 2;
			translate = translate2;
			scale = scale2;
			rot = rot2;
			check = 2;
		}
		if (glfwGetKey(window, GLFW_KEY_3)) {
			id = 3;
			translate = translate3;
			scale = scale3;
			rot = rot3;
			check = 3;
		}
		if (glfwGetKey(window, GLFW_KEY_4)) {
			id = 4;
			translate = translate4;
			scale = scale4;
			rot = rot4;
			check = 4;
		}
		if (glfwGetKey(window, GLFW_KEY_5)) {
			id = 5;
			translate = translate5;
			scale = scale5;
			rot = rot5;
			check = 5;
		}
		if (glfwGetKey(window, GLFW_KEY_6)) {
			id = 6;
			translate = translate6;
			scale = scale6;
			rot = rot6;
			check = 6;
		}
		if (glfwGetKey(window, GLFW_KEY_7)) {
			id = 7;
			translate = translate7;
			scale = scale7;
			rot = rot7;
			check = 7;
		}
		if (glfwGetKey(window, GLFW_KEY_DELETE)) {
			id = 999;
		}

		// view/projection transformations
		glm::vec4 viewPort = glm::vec4(0.0f, 0.0f, SCR_WIDTH, SCR_HEIGHT);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		// transform
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		glm::mat4 mouseProjection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 3.0f);
		glm::vec3 screenFar = glm::vec3(x, SCR_HEIGHT - y - 1, -1.0f);
		glm::vec3 screenNear = glm::vec3(x, SCR_HEIGHT - y - 1, 1.0f);
		glm::vec3 worldFar = glm::unProject(screenFar, view, mouseProjection, viewPort);
		glm::vec3 worldNear = glm::unProject(screenNear, view, mouseProjection, viewPort);
		glm::vec3 worldFinal = worldNear - worldFar;

		//MOUSE
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
			translate = glm::mat4();
			translate = glm::translate(translate, glm::vec3(worldFinal.x, worldFinal.y, 0.0f));
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT && GLFW_PRESS)) {
			id = 998;
			glfwSetCursorPosCallback(window, mouse_callback);
			if (X1 <= 135 && Y1 <= 563)
			{
				id = 3;
			}
		}
		//END MOUSE


		//INIT
		if (id == 0)
		{

			scale1 = glm::scale(scale, glm::vec3(0.1f, 0.1f, 0.1f));
			rot1 = rot;
			translate1 = glm::translate(translate, glm::vec3(-1.0f, -1.0f, -1.0f));

			scale2 = glm::scale(scale, glm::vec3(0.2f, 0.2f, 0.2f));
			rot2 = rot;
			translate2 = glm::translate(translate, glm::vec3(-1.0f, -1.0f, -3.5f));

			scale3 = glm::scale(scale, glm::vec3(0.2f, 0.2f, 0.2f));
			rot3 = rot;
			translate3 = glm::translate(translate, glm::vec3(-1.0f, -1.0f, -4.0f));

			scale4 = glm::scale(scale, glm::vec3(0.2f, 0.2f, 0.2f));
			rot4 = rot;
			translate4 = glm::translate(translate, glm::vec3(-1.0f, -1.0f, -5.0f));


			scale5 = glm::scale(scale, glm::vec3(0.2f, 0.2f, 0.2f));
			rot5 = rot;
			translate5 = glm::translate(translate, glm::vec3(-2.0f, 0.0f, -1.0f));

			scale6 = glm::scale(scale, glm::vec3(0.2f, 0.2f, 0.2f));
			rot6 = rot;
			translate6 = glm::translate(translate, glm::vec3(-2.0f, 0.0f, -1.0f));

			scale7 = glm::scale(scale, glm::vec3(0.2f, 0.2f, 0.2f));
			rot7 = rot;
			translate7 = glm::translate(translate, glm::vec3(-2.0f, 0.0f, -1.0f));
		}

		// FIRST OBJECT
		// render the loaded model
		if (id == 1) {
			translate1 = translate;
			scale1 = scale;
			rot1 = rot;

		}
		glm::mat4 model;
		model = model * translate1 * scale1 * rot1;
		ourShader.setMat4("model", model);
		ourModel1.Draw(ourShader);
		// END FIRST OBJECT

		// SECOND OBJECT
		if (id == 2)
		{
			translate2 = translate;
			scale2 = scale;
			rot2 = rot;
		}
		glm::mat4 model2;
		model2 = model2 * translate2 * scale2 * rot2;
		ourShader.setMat4("model", model2);
		ourModel2.Draw(ourShader);
		// END SECOND OBJECT

		// THIRD OBJECT
		if (id == 3)
		{
			translate3 = translate;
			scale3 = scale;
			rot3 = rot;
		}
		glm::mat4 model3;
		model3 = model3 * translate3 * scale3 * rot3;
		ourShader.setMat4("model", model3);
		ourModel3.Draw(ourShader);
		// END THIRD OBJECT

		// FOURTH OBJECT
		if (id == 4)
		{
			translate4 = translate;
			scale4 = scale;
			rot4 = rot;
		}
		glm::mat4 model4;
		model4 = model4 * translate4 * scale4 * rot4;
		ourShader.setMat4("model", model4);
		ourModel4.Draw(ourShader);
		// END FOURTH OBJECT
		// FOURTH OBJECT
		if (id == 5)
		{
			translate5 = translate;
			scale5 = scale;
			rot5 = rot;
		}
		glm::mat4 model5;
		model5 = model5 * translate5 * scale5 * rot5;
		ourShader.setMat4("model", model5);
		ourModel5.Draw(ourShader);
		// END FOURTH OBJECT
		if (id == 6)
		{
			translate6 = translate;
			scale6 = scale;
			rot6 = rot;
		}
		glm::mat4 model6;
		model6 = model6 * translate6 * scale6 * rot6;
		ourShader.setMat4("model", model6);
		ourModel6.Draw(ourShader);

		if (id == 7)
		{
			translate7 = translate;
			scale7 = scale;
			rot7 = rot;
		}
		glm::mat4 model7;
		model7 = model7 * translate7 * scale7 * rot7;
		ourShader.setMat4("model", model7);
		ourModel7.Draw(ourShader);

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
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}



//MENAGTUR CAMERA
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//SAAT SCROLL DIGERAKAN
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset == 1)
		scale = glm::scale(scale, glm::vec3(1.2f));
	if (yoffset == -1)
		scale = glm::scale(scale, glm::vec3(0.8f));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_UP))
		rot = glm::rotate(rot, -0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		rot = glm::rotate(rot, 0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		rot = glm::rotate(rot, -0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
		rot = glm::rotate(rot, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		X1 = xpos;
		Y1 = ypos;
		firstMouse = false;
	}
}