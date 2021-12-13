#include "gGlfwWindow.h"

#pragma region WINDOWCALLBACKS


void gGlfwWindow::window_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetFramebufferSize(window, &width, &height);
	cout << "GLFW: WINDOW RESIZED\n";
}
void gGlfwWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetFramebufferSize(window, &width, &height);
	cout << "GLFW: WINDOW SHOULD BE REFRESHED\n";
}

void gGlfwWindow::window_refresh_callback(GLFWwindow* window)
{
	cout << "GLFW: WINDOW SHOULD BE REFRESHED\n";
}
void gGlfwWindow::window_pos_callback(GLFWwindow* window, int x, int y)
{

}
void gGlfwWindow::window_focus_callback(GLFWwindow* window, int focused)
{

}
void gGlfwWindow::window_iconify_callback(GLFWwindow* window, int iconified)
{

}
void gGlfwWindow::window_maximize_callback(GLFWwindow* window, int maximized)
{
	if (maximized)
	{
		// The window was maximized

	}
	else
	{
		// The window was restored

	}
}
#pragma endregion

void gGlfwWindow::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if ((button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_LEFT) && action == GLFW_PRESS) {
		cout << "GLFW: WINDOW CLICKED\n";
	}

}

GLFWwindow* gGlfwWindow::initialize(int width, int height, int2 pos) {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);
	/*
	---WINDOW-CREATE-OPTIONS-(HINTS)
	*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
	glfwWindowHint(GLFW_FLOATING, 1);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 0);
	glfwWindowHint(GLFW_SAMPLES, 8);

	window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//glfwSetWindowAspectRatio(window, 16, 9);
	glfwRequestWindowAttention(window);

	/*REGISTER WINDOW EVENT CALLBACKS*/
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);
	glfwSetWindowPosCallback(window, window_pos_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowFocusCallback(window, window_iconify_callback);
	glfwSetWindowMaximizeCallback(window, window_maximize_callback);
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1/*DEFAULT IS 1*/);

	return window;
}