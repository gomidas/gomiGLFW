#pragma once
#ifndef _CONTROLSRENDERER_
#define _CONTROLSRENDERER_

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <linmath.h>

#endif

static class ControlsRenderer {
public: void RenderPixels(GLFWwindow* window, unsigned char data[100 * 100 * 3]);
};