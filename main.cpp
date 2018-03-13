#define _CRT_SECURE_NO_WARNINGS

#include "main.h"

#include "transform.h"
#include "include/glew.h"
#include "include/glfw3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
static const GLfloat identity_matrix[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f ,0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

static const GLchar *VertexShaderSource = {
	"#version 430 core\n"
	"\n"
	"layout(location = 0) in vec4 vPosition;\n"
	"\n"
	"uniform mat4 model_matrix;\n"
	"uniform mat4 projection_matrix;\n"
	"\n"
	"void main()\n"
	"{\n"
	"gl_Position = projection_matrix * model_matrix * vPosition;\n"
	"}\n"
};
static const GLchar *FragmentShaderSource = {
	"#version 430 core\n"
	"\n"
	"out vec4 fColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"fColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
	"}\n"
};

static const GLbyte axes[][3] = {
	{ -1, 0, 0 },{ 1, 0, 0 },
	{ 0, -1, 0 },{ 0, 1, 0 }
};

static const GLfloat projection_matrix[] = {
	2.0f / 1000, 0.0f, 0.0f, 0.0f,
	0.0f, 2.0f / 1000, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLuint render_prog;
GLuint vertex_shader, fragment_shader;
GLint render_model_matrix_loc, render_projection_matrix_loc;

GLFWwindow *window;

GLuint numVertices;

GLfloat transformation_matrix[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

void initialize() {
	// Initialize and Create a Window
	glfwInit();
	window = glfwCreateWindow(1000, 1000, "Tugas Besar II IF2123 Aljabar Geometri", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewInit();

	// Load Arrays
	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumBuffers, Buffers);

	glBindVertexArray(VAOs[Polygon]);
	scanf("%d", &numVertices);
	GLuint size = numVertices * sizeof(struct Vertex);
	struct Vertex *vertices = (struct Vertex *)malloc(size);
	for (GLuint i = 0; i < numVertices; i++) {
		scanf("%d,%d,%d", &vertices[i].x, &vertices[i].y, &vertices[i].z);
	}
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PolygonVertices]);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	free(vertices);

	glBindVertexArray(VAOs[Axes]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[AxesVertices]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 3, GL_BYTE, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);

	// Load Shaders
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragment_shader);

	render_prog = glCreateProgram();
	glAttachShader(render_prog, vertex_shader);
	glAttachShader(render_prog, fragment_shader);
	glLinkProgram(render_prog);

	render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
	render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");

	glUseProgram(render_prog);
}

void display() {
	glClearBufferfv(GL_COLOR, 0, black);

	glBindVertexArray(VAOs[Polygon]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[PolygonVertices]);
	glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_TRUE, projection_matrix);
	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_TRUE, transformation_matrix);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);
	
	glBindVertexArray(VAOs[Axes]);
	glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_TRUE, identity_matrix);
	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_TRUE, identity_matrix);
	glDrawArrays(GL_LINES, 0, sizeof(axes) / sizeof(axes[0]));
}

void finalize() {
	glUseProgram(0);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glDeleteProgram(render_prog);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(NumBuffers, Buffers);

	glBindVertexArray(0);
	glDeleteVertexArrays(NumVAOs, VAOs);

	glfwDestroyWindow(window);
	glfwTerminate();
}

int main(int argc, char *argv[]) {
	initialize();
	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();

		char input[10];
		scanf("%s", input);
		if (strcmp(input, "multiple") == 0)
		{
			unsigned int n;
			scanf("%d", &n);
			Multiple(transformation_matrix, n);
		}
		else if (strcmp(input, "reset") == 0)
		{
			Reset(transformation_matrix);
		}
		else if (strcmp(input, "exit") == 0)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		else
		{
			Transform(transformation_matrix, input);
		}
	}
	finalize();
}