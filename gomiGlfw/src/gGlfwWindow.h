#pragma once

#ifndef _GGLFWWINDOW_
#define _GGLFWWINDOW_
#include <stdlib.h>
#include "myMath.h"
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#endif


class gGlfwWindow
{
public:
	gGlfwWindow() {};
	GLFWwindow* initialize(int width, int height, int2 pos);

	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void window_refresh_callback(GLFWwindow* window);
	static void window_pos_callback(GLFWwindow* window, int x, int y);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_maximize_callback(GLFWwindow* window, int maximized);
	static void error_callback(int error, const char* description);
	~gGlfwWindow();
};