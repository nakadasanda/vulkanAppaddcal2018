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
	_InitSwapchain();
}



Window::~Window()
{
	_DeInitSwapchain();

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
	std::cout << "maxImageArrayLayers: " << _surface_capabilities.maxImageArrayLayers << std::endl;
	std::cout << "supportedTransforms: " << _surface_capabilities.supportedTransforms << std::endl;
	std::cout << "currentTransform: " << _surface_capabilities.currentTransform << std::endl;
	std::cout << "supportedCompositeAlpha: " << _surface_capabilities.supportedCompositeAlpha << std::endl;
	std::cout << "supportedUsageFlags: " << _surface_capabilities.supportedUsageFlags << std::endl;
	std::cout << std::endl;
	{

		uint32_t format_count = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, _surface, &format_count, nullptr);
		std::vector<VkSurfaceFormatKHR>formats(format_count);
		vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, _surface, &format_count, formats.data());
		std::cout << "DeviceSurfaceFormats: " << format_count << std::endl;
		for (int i = 0; i < format_count;i++) {
			std::cout << "Format: " << formats[i].format << std::endl;
		}
	}
	std::cout << std::endl;
	
}



void Window::_DeInitSurface()
{

	vkDestroySurfaceKHR(_renderer->GetVulkanInstance(), _surface, nullptr);
}

void Window::_InitSwapchain()
{
	if (_swapchain_image_count > _surface_capabilities.maxImageCount) _swapchain_image_count = _surface_capabilities.maxImageCount;
	if (_swapchain_image_count < _surface_capabilities.minImageCount + 1) _swapchain_image_count = _surface_capabilities.minImageCount + 1;

	VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
	{
		uint32_t present_mode_count;
		vkGetPhysicalDeviceSurfacePresentModesKHR(_renderer->GetVulkanPhysicalDevice(),_surface, &present_mode_count, nullptr);
		std::vector<VkPresentModeKHR>present_mode_list(present_mode_count);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_renderer->GetVulkanPhysicalDevice(), _surface, &present_mode_count, present_mode_list.data());
		std::cout << "DeviceSurfaceFormats: " << present_mode_count << std::endl;
		for (int i = 0; i < present_mode_count; i++) {
			std::cout << "support present mode: " << present_mode_list[i] << std::endl;
		}
		
	}
	

	VkBool32 surfaceSupport;
	vkGetPhysicalDeviceSurfaceSupportKHR(_renderer->GetVulkanPhysicalDevice(), 0, _surface, &surfaceSupport);
	if (VK_TRUE != surfaceSupport) {
		assert(0 && "Vulkan Err :not support Swapchain ");
		std::exit(-1);
	}

	VkSwapchainCreateInfoKHR swapchain_create_info = {};
	swapchain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchain_create_info.pNext = nullptr;
	swapchain_create_info.flags = 0;
	swapchain_create_info.surface = _surface;
	swapchain_create_info.minImageCount = _swapchain_image_count;
	swapchain_create_info.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
	swapchain_create_info.imageColorSpace = _surface_format.colorSpace;
	swapchain_create_info.imageExtent.width = _surface_size_x;
	swapchain_create_info.imageExtent.height = _surface_size_y;
	swapchain_create_info.imageArrayLayers = 1;
	swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchain_create_info.queueFamilyIndexCount = 0;
	swapchain_create_info.pQueueFamilyIndices = nullptr;
	swapchain_create_info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_create_info.presentMode = VK_PRESENT_MODE_FIFO_KHR;
	swapchain_create_info.clipped =VK_TRUE;
	swapchain_create_info.oldSwapchain = VK_NULL_HANDLE;
	
	vkCreateSwapchainKHR(_renderer->GetVulkanDevice(),&swapchain_create_info,nullptr,&_swapchain);
	
}


void Window::_DeInitSwapchain()
{
	vkDestroySwapchainKHR(_renderer->GetVulkanDevice(), _swapchain ,nullptr);
}
