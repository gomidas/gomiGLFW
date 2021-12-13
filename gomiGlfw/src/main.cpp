#include <stdio.h>
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "linmath.h"

#include <stdlib.h>

#include <iostream>
#include <string.h>
#include <thread>
#include <sstream>


#include "myMath.h"
#include "MyColor.h"
//FREETYPE
#include "fontRenderer.h"
#include "ControlsRenderer.h"
#include <list>
#include "MyGeometry.h"
#include "MyFileOperationscpp.cpp"
#include "gGlfwWindow.h"

#define DEG2RAD 3.14159/180

using namespace std;
extern "C" {
	_declspec(dllexport) unsigned int NvOptimusEnablement = 0x00000001;
}
GLuint vertex_buffer, vertex_shader, fragment_shader, program, multisampledFBO, tex_handle;
GLint mvp_location, vpos_location, vcol_location, tex_location;
char* EXEPath;

list<TextObject*> textObjects;
int width, height;

static const struct
{
	float r, g, b;
	float x, y, z;
	float u, v;
} vertices[6] =
{
	{ -0.6f, -0.4f, 0.f,   1.f, 0.f, 0.f,  1.f,1.f },
	{  0.6f, -0.4f, 0.f,   0.f, 1.f, 0.f,  0.f, 1.f },
	{   0.f,  0.6f, 0.f,   0.f, 0.f, 0.f,  0.f,0.f },

	{ -0.6f, -0.4f, 0.f,   1.f, 1.f, 0.f,  1.f,1.f },
	{  0.6f, -0.4f, 0.f,   0.f, 1.f, 0.f,  1.f, 0.f },
	{   0.f,  0.6f, 0.f,   1.f, 0.f, 1.f,  0.f,1.f }
};

#pragma region Shaders
static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
"layout(location = 1) in vec2 vertexUV;\n"
"out vec2 UV;\n"
"void main()\n"
"{\n"
"gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);\n"
"UV = vertexUV;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330\n"
"out vec3 FragColor;\n"
"in vec2 UV;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"    FragColor = texture(ourTexture, UV).rgb;\n"
"}\n";
#pragma endregion
static char* ExePath;
string getExePath(string ExePath) {
	string path = ExePath; int a = path.find_last_of('\\'); path = path.substr(0, a);
	//cout << path << "  -first\n";
	return path;
}
void printTime(GLFWwindow* window) {
	while (window) {
		glfwSetWindowTitle(window, to_string((double)glfwGetTime()).c_str()); this_thread::sleep_for(200ms);
	}
}

#pragma region LoadTexture

unsigned char* init_texture(string path, string fileName)
{

	string ImagePath;
	ImagePath.append(path).append("\\").append(fileName);

	glGenTextures(1, &tex_handle);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_handle);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(ImagePath.c_str(), &width, &height, &nrChannels, STBI_rgb);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
		return data;
	}
	else
	{
		printf("failed to load texture");
		return 0;
	}

	stbi_image_free(data);
}
void unbind_texture() {
	//glBindTexture(texture, 0);
	glDisable(GL_TEXTURE_2D);
}
#pragma endregion

#pragma region Draw
void Draw(GLFWwindow* window, GLuint program, GLint mvp_location, char* ExePath)
{
	Circle* circle = new Circle(0.25f, 2.5f, RGBTOFRGB(255, 127, 39)/*COLORNAME::ORANGE */, FRGB(0.25f, 0.5f, 1.0f), "NEWCIRCLE1");
	cout << circle->Animations.size() << "\n";
	circle->AddAnimation(2.0f, GeometryAnimation::AnimAttribute::Color, "colorAnim1");

	TextObject* textObject = new TextObject(64, float3(1.0f, 0.0f, 1.0f), 1, "g");
	string FontPathStr = BuildStringToFilePath(getExePath(ExePath), "Armguard.ttf");
	cout << FontPathStr;

	if (!IsFileExists("Armguard.ttf"))
	{
		cout << "FILE READ: READ FAULT. FILE IS NOT THERE OR PATH IS WRONG\n";
	}
	else
	{
		textObject->initFreeType2();
		bool result = textObject->loadFontToMemory((char*)(FontPathStr.c_str()), tex_handle);
		if (result)
		{
			textObjects.push_back(textObject);
			//if (textObject->fontFace->glyph) cout << "FT2 FF FontFamily: " << textObject->fontFace->glyph->face->family_name << "\n";
		}
	}

	glfwMakeContextCurrent(window);
	unsigned char*data = init_texture(getExePath(ExePath), "uv_test.png");
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		float ratio;
		mat4x4 m, p, mvp;

		ratio = width / (float)height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glEnd();

		circle->Render(window);

		textObject->Render(window, tex_handle);

		glfwSwapBuffers(window);

		this_thread::sleep_for(10ms);
	}
}
#pragma endregion


#pragma region MainThread
int main(int argc, char* argv[])
{
	EXEPath = argv[0];
	gGlfwWindow *gwindow = new gGlfwWindow();
	GLFWwindow* window = gwindow->initialize(800,600,int2(100,100));

	thread td1(printTime, window);

	// NOTE: OpenGL error checks have been omitted for brevity
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vertexUV"); //vertexUV
	vcol_location = glGetAttribLocation(program, "vertexPosition_modelspace"); //vertexPosition_modelspace

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(float) * 6));

	glEnable(GL_MULTISAMPLE);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampledFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glfwMakeContextCurrent(NULL);

	thread td2(Draw, window, program, mvp_location, argv[0]);

	while (!glfwWindowShouldClose(window))
	{
		//glfwSwapBuffers(window);
		glfwPollEvents();
		//glfwWaitEvents();
	}
	td2.join();

	auto txt_objs = textObjects.begin();
	for (int i = 0; i < textObjects.size(); i++)
	{
		advance(txt_objs, i);
		dynamic_cast<TextObject*>(*txt_objs)->~TextObject();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
#pragma endregion
