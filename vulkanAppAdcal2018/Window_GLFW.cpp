#include "Platform.h"

#include "Window.h"
#include <assert.h>


#if VK_USE_PLATFORM_WIN32_KHR

void Window::_InitWindow() 
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_GLFW_window = glfwCreateWindow(_surface_size_x,_surface_size_y, _window_name.c_str(),nullptr,nullptr);

}

void Window::_DeInitWindow()
{
	glfwDestroyWindow(_GLFW_window);
}

void Window::_UpdateWindow()
{
	while (true){
		glfwPollEvents();
	};
}

#endif