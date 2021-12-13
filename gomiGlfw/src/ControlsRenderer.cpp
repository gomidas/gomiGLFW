#include "ControlsRenderer.h"

void ControlsRenderer::RenderPixels(GLFWwindow* window, unsigned char data[100*100*3])
{
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			data[y * 100 * 3 + x * 3] = 0xff;
			data[y * 100 * 3 + x * 3 + 1] = 0x00;
			data[y * 100 * 3 + x * 3 + 2] = 0x00;
		}
	}
	
	for (int y = 25; y < 75; y++)
	{
		for (int x = 25; x < 75; x++)
		{
			data[y * 100 * 3 + x * 3] = 0x00;
			data[y * 100 * 3 + x * 3 + 1] = 0xff;
			data[y * 100 * 3 + x * 3 + 2] = 0x00;
		}
	}

	for (int y = 50; y < 55; y++)
	{
		for (int x = 50; x < 55; x++)
		{
			data[y * 100 * 3 + x * 3] = 0x00;
			data[y * 100 * 3 + x * 3 + 1] = 0x00;
			data[y * 100 * 3 + x * 3 + 2] = 0xff;
		}
	}

	//glUseProgram(0);
	//glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
	glEnd();

}