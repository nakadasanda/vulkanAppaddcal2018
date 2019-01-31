#include "Window.h"
#include <assert.h>
#include <iostream>


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
	_DeInitSurface();

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
	
	std::cout << std::endl;
	std::cout << "DeviceSurfaceCapabilities" << std::endl;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, _surface, &_surface_capabilities);
	std::cout << "minImageCount " << _surface_capabilities.minImageCount << std::endl;
	std::cout << "maxImageCount " << _surface_capabilities.maxImageCount << std::endl;
	std::cout << "currentExtent: (width, height) " << "( "<< _surface_capabilities.currentExtent.width << ", " << _surface_capabilities.currentExtent.height << " )" << std::endl;
	std::cout << "minImageExtent: (width, height) " << "( " << _surface_capabilities.minImageExtent.width << ", " << _surface_capabilities.minImageExtent.height << " )" << std::endl;
	std::cout << "maxImageArrayLayers " << _surface_capabilities.maxImageArrayLayers << std::endl;
	std::cout << "supportedCompositeAlpha" << _surface_capabilities.supportedCompositeAlpha << std::endl;
	std::cout << "supportedTransforms " << _surface_capabilities.supportedTransforms << std::endl;
	std::cout << "currentTransform " << _surface_capabilities.currentTransform << std::endl;
	std::cout << " supportedCompositeAlpha " << _surface_capabilities.supportedCompositeAlpha << std::endl;
	std::cout << "supportedUsageFlags" << _surface_capabilities.supportedUsageFlags << std::endl;
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