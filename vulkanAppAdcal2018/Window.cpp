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
	_InitSwapchainImages();
}



Window::~Window()
{
	_DeInitSwapchainImages();
	_DeInitSwapchain();
	_DeInitSurface();
	_DeInitOSWindow();

}

std::vector<VkImageView> Window::GetImageview()
{
	return _swapchain_image_view;
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


	VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
	{
		//プレゼンモードチェック
		uint32_t present_mode_count;
		vkGetPhysicalDeviceSurfacePresentModesKHR(_renderer->GetVulkanPhysicalDevice(),_surface, &present_mode_count, nullptr);
		std::vector<VkPresentModeKHR>present_mode_list(present_mode_count);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_renderer->GetVulkanPhysicalDevice(), _surface, &present_mode_count, present_mode_list.data());
		std::cout << "DeviceSurfaceFormats: " << present_mode_count << std::endl;
		for (int i = 0; i < present_mode_count; i++) {
			std::cout << "support present mode: " << present_mode_list[i] << std::endl;
		}
		
	}
	
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_renderer->GetVulkanPhysicalDevice(), _surface, &_surface_capabilities);

	//描写フォーマットチェック
	uint32_t format_count = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(_renderer->GetVulkanPhysicalDevice(), _surface, &format_count, nullptr);
	std::vector<VkSurfaceFormatKHR>formats(format_count);
	vkGetPhysicalDeviceSurfaceFormatsKHR(_renderer->GetVulkanPhysicalDevice(), _surface, &format_count, formats.data());
	std::cout << "DeviceSurfaceFormats: " << format_count << std::endl;
	for (int i = 0; i < format_count; i++) {
		std::cout << "Format: " << formats[i].format << std::endl;
		std::cout << "ColorSpace: " << formats[i].colorSpace << std::endl;
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
	swapchain_create_info.clipped = VK_TRUE;
	swapchain_create_info.oldSwapchain = VK_NULL_HANDLE;
	
	 auto err = vkCreateSwapchainKHR(_renderer->GetVulkanDevice(),&swapchain_create_info,nullptr,&_swapchain);
	 if (VK_SUCCESS != err) {
		 assert(0 && "Vulkan ERROR: Create swapchain failed!!");
		 std::exit(-1);
	 }
	
}


void Window::_DeInitSwapchain()
{
	vkDestroySwapchainKHR(_renderer->GetVulkanDevice(), _swapchain ,nullptr);
}

void Window::_InitSwapchainImages()
{

	vkGetSwapchainImagesKHR(_renderer->GetVulkanDevice(), _swapchain, &_swapchain_image_count, nullptr);
	
	_swapchain_Image.resize(_swapchain_image_count);
	_swapchain_image_view.resize(_swapchain_image_count);
	vkGetSwapchainImagesKHR(_renderer->GetVulkanDevice(), _swapchain, &_swapchain_image_count, _swapchain_Image.data());

	
	for (int i = 0; i < _swapchain_image_count; i++) {
		VkImageViewCreateInfo image_view_create_info{};
		
		image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		image_view_create_info.pNext = nullptr;
		image_view_create_info.flags = 0;
		image_view_create_info.image = _swapchain_Image[i];
		image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		image_view_create_info.format = VK_FORMAT_B8G8R8A8_UNORM;
		image_view_create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		image_view_create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		image_view_create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		image_view_create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		image_view_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		image_view_create_info.subresourceRange.baseMipLevel = 0;
		image_view_create_info.subresourceRange.levelCount = 1;
		image_view_create_info.subresourceRange.baseArrayLayer = 0;
		image_view_create_info.subresourceRange.layerCount = 1;


		vkCreateImageView(_renderer->GetVulkanDevice(), &image_view_create_info, nullptr, &_swapchain_image_view[i]);
	}
}

void Window::_DeInitSwapchainImages()
{
	for (auto view : _swapchain_image_view) {
		vkDestroyImageView(_renderer->GetVulkanDevice(),view,nullptr);
	}
}
