#include "Window.h"
#include <assert.h>



Window::Window(Renderer * renderer, uint32_t size_x, uint32_t size_y, std::string name)
{
	_renderer = renderer;
	_surface_size_x = size_x;
	_surface_size_x = size_y;
	_window_name = name;
	_InitOSWindow();
	_InitSurface();
}



Window::~Window()
{
	_DeInitOSWindow();
}

void Window::Close()
{
	_window_should_run = false;
}

bool Window::Update()
{
	_UpdateOSWindow();
	return _window_should_run;
}

void Window::_InitSurface()
{
	_InitOSSurface();
	
	auto gpu = _renderer->GetVulkanPhysicalDevice();
	VkBool32 WSI_supported = false;
	vkGetPhysicalDeviceSurfaceSupportKHR(gpu, _renderer->GetVulkanQueueFamilyIndex(), _surface, &WSI_supported);
	
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, _surface, &_surface_capabilities);
	{
		uint32_t format_count = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, _surface, &format_count, nullptr);
		std::vector<VkSurfaceFormatKHR>formats(format_count);
		vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, _surface, &format_count, formats.data());
	}
	
}

void Window::_DeInitSurface()
{

}