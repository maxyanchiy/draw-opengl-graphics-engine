#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

GLuint VAO, VBO, shader, uniformModel;
float triOffsetDirection = 1.f;
float triOffset = 0.0f;
constexpr float triMaxOffset = 0.7f;
constexpr float triIncrement = 0.01f;
const float toRadians = 3.14159265f / 180.f;

// Vertex shader
static const char* vShader = "     \n\
#version 330                       \n\
layout (location = 0) in vec3 pos; \n\
uniform mat4 model;               \n\
void main()                        \n\
{                                  \n\
	gl_Position = model*vec4(0.4*pos.x, 0.4*pos.y, 0.4*pos.z, 1.0);      \n\
}                                  \n\
";

// Fragment Shader
static const char* fShader = "     \n\
#version 330                       \n\
out vec4 colour; \n\
void main()                        \n\
{                                  \n\
	colour = vec4(1.0, 0.0, 0.0, 1.0);      \n\
}                                  \n\
";

void CreateTriangle()
{
	GLfloat vertices[] = {
		-1.f, -1.f, 0.f,
		1.0f, -1.f, 0.f,
		0.f, 1.f, 0.0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void AddShader(GLuint program, const char* shaderCode, GLenum shaderType) {
	GLuint newShader = glCreateShader(shaderType);
	const GLchar* newShaderCode[1];
	newShaderCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(newShader, 1, newShaderCode, codeLength);
	glCompileShader(newShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(newShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(newShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling %d shader: '%s' \n", shaderType, eLog);
		return;
	}

	glAttachShader(program, newShader);
}

void CompileShaders() {
	shader = glCreateProgram();
	if (!shader)
	{
		printf("Error creating shader prog!\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s' \n", eLog);
		return;
	}

	glValidateProgram(shader);
	uniformModel = glGetUniformLocation(shader, "model");
}

int main() {

	if (!glfwInit())
	{
		printf("GLFW init failed");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "dRaw", NULL, NULL);

	if (!mainWindow)
	{
		printf("GLFW window failed");
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW init failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriangle();
	CompileShaders();

	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();
		glClearColor(0.f, 0.4375f, 0.4375f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 model(1.f);
		//model = glm::translate(model, glm::vec3(triOffset, 0.f, 0.f));
		//model = glm::rotate(model, 60.f * toRadians, glm::vec3(0.f, 0.f, 1.f));
		model = glm::scale(model, glm::vec3(2.f, 2.f, 1.f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

		if (std::abs(triOffset) >= triMaxOffset)
		{
			triOffsetDirection *= -1.f;
		}
		triOffset += triOffsetDirection*triIncrement;
	}

	return 0;
}