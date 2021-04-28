/* #include <X11/X.h>
#include <X11/Xlib.h> */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>

int main()
{
	
	if( !glfwInit() )
	{
		fprintf(stderr, "Failed to initialize openGL");
		return -1;
	}


	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World!", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), points,GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);

	FILE *vs_shad_file = fopen("test_vs.glsl", "r");
	FILE *fs_shad_file = fopen("test_fs.glsl", "r");

	if(vs_shad_file == NULL)
	{
		printf("kusi");
	}
	char* buff1[1000];
	char* buff2[1000];
	const char* fs_shad =
	"#version 400\n"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(1.0, 0.0, 1.0, 1.0);"
	"}";

	fread( buff1, 1, 1000, vs_shad_file);
	const char* vertex_shader = buff1;
	fread( buff2, 1, 1000, fs_shad_file);
	const char* fragment_shader = buff2;
	fclose(vs_shad_file);
	fclose(fs_shad_file);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_shad, NULL);
	glCompileShader(fs);
	GLuint shader_programme = glCreateProgram;
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
		glfwSwapBuffers(glfwGetCurrentContext());
	}

	glfwTerminate();
	return 0;
}