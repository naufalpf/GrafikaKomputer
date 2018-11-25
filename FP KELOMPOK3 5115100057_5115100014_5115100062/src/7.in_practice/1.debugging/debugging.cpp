
//langkah 1: masukkan lib glad dan glfw
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <learnopengl/filesystem.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream> //untuk fungsi input output
#include <fstream>
#include <windows.h>
#define NR_POINT_LIGHTS 12
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const * path);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
stringstream cahaya;
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
GLFWwindow* window;

bool firstMouse = true;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
void init()
{

	//langkah 2: membuat window pada GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//Memberitahu bahwa versi opengl yang digunakan 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//langkah 3: membuat window object
	//GLFWwindow* window = glfwCreateWindow(800, 600, "Belajar Membuat segitiga", NULL, NULL);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FP _ 5115100082 _ 5115100109", NULL, NULL);


	if (window == NULL)
	{
		std::cout << "Gagal membuat GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}
	glfwMakeContextCurrent(window);
	//langkah 6: memberi tahu GLFW untuk memanggil fungsi frame_buffer_size_callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//langkah 4: menginisialisasi GLAD, GLAD digunakan untuk memanggil fungsi2 openGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Gagal menginisialisasi GLAD" << std::endl;
		glfwTerminate();
		//return -1;

	}
}

int main()
{



	init();

	//bagian yang berhubungan dengan shader

	Shader ourShader("v_shader_lamp.vs", "f_shader_lamp.fs");
	Shader dummmyShader("v_shader_lamp.vs", "f_shader_lamp.fs");
	Shader lampShader("v_shader.vs", "f_shader.fs");
	Shader modelShader("v_shader_model.vs", "f_shader_model.fs");
	Shader kotakShader("v_shader_lamp.vs", "f_shader_kotak.fs");
	/*char filename[] = "nanosuit2.obj";
	char fullFileName[MAX_PATH];

	GetFullPathName(filename, MAX_PATH, fullFileName, nullptr);
	cout << fullFileName;
	Model ourModel(fullFileName);*/
	//Model ourModel(FileSystem::getPath("resources/objects/notebook/notebook.obj"));
	/**************Akhir proses inisialisasi campai proses melinkan shader**********************/

	/******************Proses inisialisasi data yang diguanakan*******************************/

	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	int numPolys, numLines;
	GLfloat x, y;
	GLint Poly[100];



	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};


	glm::vec3 enviroPosition[6]{
		glm::vec3(0.0f, 3.5f, -7.75f),
		glm::vec3(0.0f, 3.5f, 0.0f),
		glm::vec3(-2.5f, 3.5f, -5.5f),
		glm::vec3(2.5f, 3.5f, -1.0f),
		glm::vec3(4.0f,3.5f,2.5f),
		glm::vec3(-4.0f,3.5f,3.5f)
	};

	glm::vec3 mainKotak[6]{
		glm::vec3(0.0f, -1.25f, 0.0f),
		glm::vec3(2.0f, -1.25f, 0.0f),
		glm::vec3(-4.0f, -1.25f, 13.0f),
		glm::vec3(0.0f, -1.25f, 2.0f),
		glm::vec3(14.0f, -1.25f, 0.0f),
		glm::vec3(-5.0f, -1.25f, -2.0f)
	};

	glm::vec3 lightColor[24]{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)

	};

	//proses membuat object VBO dan VAO

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);



	unsigned int lampVAO;
	glGenVertexArrays(1, &lampVAO);
	glBindVertexArray(lampVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int diffuseMap = loadTexture(("./container2.png"));
	unsigned int specularMap = loadTexture(("./container2_specular.png"));

	//proses render
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glUseProgram(shaderProgram);

		glBindVertexArray(lampVAO);
		lampShader.use();

		//glm::mat4 view;
		//glm::mat4 projection;
		//glm::mat4 projection;

		lampShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);

		// world transformation


		for (int i = 0; i<6; i++) {
			/*glm::mat4 model;
			lampShader.setVec3("lightColor", lightColor[i]);
			//model = glm::rotate(model,glm::radians(50.0f),glm::vec3(1.0f,-0.3f,0.0f));
			if ((int(glfwGetTime()) % 2) == 0 && ((i % 2) == 0)) {
			model = glm::translate(model, lightPosition[i]);
			}
			else if ((int(glfwGetTime()) % 2) == 1 && ((i % 2) == 1)) {
			model = glm::translate(model, lightPosition[i]);
			}
			model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
			lampShader.setMat4("model", model);
			if ((int(glfwGetTime()) % 2) == 0 && ((i % 2) == 0)) {
			glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else if ((int(glfwGetTime()) % 2) == 1 && ((i % 2) == 1)) {
			glDrawArrays(GL_TRIANGLES, 0, 36);
			}*/
			glm::mat4 model;
			lampShader.setVec3("lightColor", lightColor[i]);
			//model = glm::rotate(model,glm::radians(50.0f),glm::vec3(1.0f,-0.3f,0.0f));
			if ((int(glfwGetTime()) % 6) == i && ((i % 6) == i)) {
				model = glm::translate(model, enviroPosition[i]);
			}
			model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
			lampShader.setMat4("model", model);
			if ((int(glfwGetTime()) % 6) == i && ((i % 6) == i)) {
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		// also draw the lamp object
		glBindVertexArray(VAO);
		ourShader.use();
		int j = 0;
		for (int i = 0; i<6; i++) {
			if ((int(glfwGetTime()) % 6) == i && ((i % 6) == i)) {
				glm::vec3 diffuseColor = lightColor[i] * glm::vec3(0.5f); // decrease the influence
				glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
				cahaya.str("");
				cahaya << "lights[" << j << "].ambient";
				ourShader.setVec3(cahaya.str(), ambientColor);
				cahaya.str("");
				cahaya << "lights[" << j << "].diffuse";
				ourShader.setVec3(cahaya.str(), diffuseColor);
				cahaya.str("");
				cahaya << "lights[" << j << "].specular";
				ourShader.setVec3(cahaya.str(), 1.0f, 1.0f, 1.0f);
				cahaya.str("");
				cahaya << "lights[" << j << "].constant";
				ourShader.setFloat(cahaya.str(), 1.0f);
				cahaya.str("");
				cahaya << "lights[" << j << "].linear";
				ourShader.setFloat(cahaya.str(), 0.045f);
				cahaya.str("");
				cahaya << "lights[" << j << "].quadratic";
				ourShader.setFloat(cahaya.str(), 0.0075f);
				cahaya.str("");
				cahaya << "lights[" << j << "].position";
				ourShader.setVec3(cahaya.str(), enviroPosition[i]);
				kotakShader.use();
				cahaya.str("");
				cahaya << "lights[" << j << "].ambient";
				kotakShader.setVec3(cahaya.str(), ambientColor);
				cahaya.str("");
				cahaya << "lights[" << j << "].diffuse";
				kotakShader.setVec3(cahaya.str(), diffuseColor);
				cahaya.str("");
				cahaya << "lights[" << j << "].specular";
				kotakShader.setVec3(cahaya.str(), 1.0f, 1.0f, 1.0f);
				cahaya.str("");
				cahaya << "lights[" << j << "].constant";
				kotakShader.setFloat(cahaya.str(), 1.0f);
				cahaya.str("");
				cahaya << "lights[" << j << "].linear";
				kotakShader.setFloat(cahaya.str(), 0.0014f);
				cahaya.str("");
				cahaya << "lights[" << j << "].quadratic";
				kotakShader.setFloat(cahaya.str(), 0.00007f);
				cahaya.str("");
				cahaya << "lights[" << j << "].position";
				kotakShader.setVec3(cahaya.str(), enviroPosition[i]);
				j++;
				if (j == NR_POINT_LIGHTS) {
					j = 0;
				}
			}
		}
		// material properties
		ourShader.use();
		ourShader.setVec3("material.diffuse", 1.1f, 0.8f, 0.4f);
		ourShader.setVec3("material.specular", 0.7f, 0.7f, 0.7f);
		ourShader.setFloat("material.shininess", 0.5f);

		ourShader.setVec3("viewPos", camera.Position);

		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		for (int i = 0; i<6; i++) {
			if ((int(glfwGetTime()) % 6) == i && ((i % 6) == i)) {
				ourShader.use();
			}
			else {
				dummmyShader.use();
			}
			glm::mat4 model;
			model = glm::mat4();
			model = glm::translate(model, enviroPosition[i]);
			float angle = 20.0f + (20.0f * glfwGetTime() * (i + 1));
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			switch (i) {
			case 0: model = glm::scale(model, glm::vec3(0.5)); break;
			case 1: model = glm::scale(model, glm::vec3(0.3)); break;
			case 2: model = glm::scale(model, glm::vec3(0.8)); break;
			case 3: model = glm::scale(model, glm::vec3(1.2)); break;
			case 4: model = glm::scale(model, glm::vec3(1.8)); break;
			default:        break;
			}
			ourShader.setMat4("model", model);
			glm::mat3 modelt;
			//karena kalo ditaroh shader nanti berat di gpu
			modelt = glm::mat3(transpose(inverse(model)));
			ourShader.setMat3("modelt", modelt);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		kotakShader.use();
		kotakShader.setInt("material.diffuse", 1.1f);
		kotakShader.setInt("material.specular", 0.7f);
		kotakShader.setFloat("material.shininess", 100.0f);
		kotakShader.setVec3("viewPos", camera.Position);

		kotakShader.setMat4("projection", projection);
		kotakShader.setMat4("view", view);
		for (int i = 0; i < 6; i++) {
			glm::mat4 model;
			model = glm::mat4();
			model = glm::translate(model, mainKotak[i]);
			kotakShader.setMat4("model", model);
			glm::mat3 modelt;
			//karena kalo ditaroh shader nanti berat di gpu
			modelt = glm::mat3(transpose(inverse(model)));
			kotakShader.setMat3("modelt", modelt);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		modelShader.use();

		// view/projection transformations
		modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);

		// render the loaded model
		glm::mat4 model;
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		modelShader.setMat4("model", model);

		//ourModel.Draw(modelShader);
		//		for (unsigned int i = 0; i < 10; i++)
		//        {
		// calculate the model matrix for each object and pass it to shader before drawing
		//            glm::mat4 model;
		//            model = glm::translate(model, cubePositions[i]);
		//            float angle = 20.0f * i;
		//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//            lampShader.setMat4("model", model);
		//
		//            glDrawArrays(GL_TRIANGLES, 0, 36);
		//        }


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//langkah terakhir: membersihkan resource yang digunakan
	glfwTerminate();
	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

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

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

