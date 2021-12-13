#pragma once
#ifndef _FONT_RENDERER_
#define  _FONT_RENDERER_
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>
#include <stdlib.h>
#include <ft2build.h>
#include "myMath.h"
#include <string.h>
#include <list>
#define FRTP "FREETYPE: "

#endif


#include FT_FREETYPE_H
static  FT_Library  library;

using namespace std;

static enum FontType
{
	light, regular, bold
};
typedef struct Character {

	 GLuint textureId;
	 float2 size; //size of char
	 float2 bearing; // distance from origin top left of char
	 signed long advance; //distance from origin to next origin

} ;
class TextObject
{


public:
	std::map<char, Character> charsData = {};

	int fontSize = 12;
	float3 fontColor = float3(0, 0, 0);
	int intfontWeight = 1;
	string Text = "";

	TextObject(int size, float3 color, int weight, string text = "") {
		fontSize = size;
		fontColor = color;
		intfontWeight = weight;
		Text = text;
		charsData = {};
	};

	void initFreeType2();
	bool loadFontToMemory(char* path, GLuint tex_handle);

	//RENDER
	void Render(GLFWwindow* window, GLuint tex_handle);
	~TextObject();
};
