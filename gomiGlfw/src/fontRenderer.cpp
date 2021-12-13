#pragma once


#include "fontRenderer.h"

using namespace std;

void TextObject::initFreeType2()
{
	FT_Error error = FT_Init_FreeType(&library);
	if (error)
	{
		//error
		cout << FRTP << "INITIALIZATION FAULT.";
	}
}
bool TextObject::loadFontToMemory(char* fontpath, GLuint tex_handle)
{
	FT_Face fontFace;

	FT_Error error = FT_Init_FreeType(&library);
	if (error) {
		cout << FRTP << "INITIALIZATION FAULT.";
	}

	error = FT_New_Face(library,
		fontpath,
		0,
		&fontFace);
	if (error == FT_Err_Unknown_File_Format)
	{
		//... the font file could be openedand read, but it appears
		//... that its font format is unsupported

		cout << FRTP << "the font file could be openedand read, but it appears. that its font format is unsupported";
		return false;
	}
	else if (error)
	{
		//... another error code means that the font file could not
		//... be opened or read, or that it is broken...
		cout << FRTP << "another error code means that the font file could not, be opened or read, or that it is broken.";
		return false;
	}


	FT_Set_Pixel_Sizes(fontFace, 0, fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	int x = 0;
	for (unsigned char i = 0; i < Text.size(); i++)
	{
		GLuint tex_handlex;
		glActiveTexture(GL_TEXTURE0);

		if (FT_Load_Char(fontFace, i, FT_LOAD_RENDER)) { continue; }
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, GL_RGB, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer);
		x += fontFace->glyph->bitmap.width;
		glGenTextures(1, &tex_handlex);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex_handlex);

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				fontFace->glyph->bitmap.width,
				fontFace->glyph->bitmap.rows,
				0,
				GL_ALPHA,
				GL_UNSIGNED_BYTE,
				fontFace->glyph->bitmap.buffer
			);

		//SET TEXTURE PARAMS
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character car = { tex_handlex, float2(fontFace->glyph->bitmap.width,fontFace->glyph->bitmap.rows), float2(fontFace->glyph->bitmap_left,fontFace->glyph->bitmap_top), fontFace->glyph->advance.x };
		charsData.insert(std::pair<char, Character>(i, car));

	}

	FT_Done_Face(fontFace);

	return true;
}

void TextObject::Render(GLFWwindow* window, GLuint tex_handle) {
	int fb_W = 0, fb_H = 0;
	glfwGetFramebufferSize(window, &fb_W, &fb_H);
	//glUseProgram(0);
	map<char, Character>::iterator it;
	for (it = charsData.begin(); it != charsData.end(); it++)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, it->second.textureId);
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();
		glOrtho(0, fb_W, 0, fb_H, -1, 1);
		glMatrixMode(GL_MODELVIEW);

		glColor4f(fontColor.x, fontColor.y, fontColor.z, 1.0f);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0); glVertex2i(0, 0);
		glTexCoord2d(1, 0); glVertex2i(0 + it->second.size.x, 0);
		glTexCoord2d(1, 1); glVertex2i(0 + it->second.size.x, it->second.size.y + 0);
		glTexCoord2d(0, 1); glVertex2i(0, it->second.size.y + 0);

		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

}

TextObject::~TextObject()
{

}