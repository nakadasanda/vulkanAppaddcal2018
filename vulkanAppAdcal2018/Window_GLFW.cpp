#include "Platform.h"

#include "Window.h"
#include <assert.h>


#if GLFW_INCLUDE_VULKAN

void Window::_InitOSWindow() 
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_GLFW_window = glfwCreateWindow(_surface_size_x,_surface_size_y, _window_name.c_str(),nullptr,nullptr);

}

void Window::_DeInitOSWindow()
{
	glfwDestroyWindow(_GLFW_window);
}

void Window::_UpdateOSWindow()
{
		glfwPollEvents();
		if (glfwWindowShouldClose(_GLFW_window)){
			Close();
		}
}

void Window::_InitOSSurface()
{
	glfwCreateWindowSurface(_renderer->GetVulkanInstance(), _GLFW_window, nullptr, &_surface);
}

#endif