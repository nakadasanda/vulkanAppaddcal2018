#include "Platform.h"

#include "Window.h"
#include <assert.h>


#if GLFW_INCLUDE_VULKAN

void Window::_InitOSWindow() 
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
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
	auto err = glfwCreateWindowSurface(_renderer->GetVulkanInstance(), _GLFW_window, nullptr, &_surface);
	if (VK_SUCCESS != err) {
		assert(0 && "Vulkan ERROR: Create swapchain failed!!");
		std::exit(-1);
	}
}

#endif