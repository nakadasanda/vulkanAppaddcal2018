#pragma once
#include <vulkan\vulkan.h>
class Renderer
{
public:
	Renderer();
	~Renderer();

private:
	void _InitInstance();
	void _DeInitInstance();

	void _InitDevise();
	void _DeInitDevice();
	
	VkInstance	_instance = nullptr;
	VkPhysicalDevice _gpu = nullptr;
	VkDevice	_devise = nullptr;
	VkPhysicalDeviceProperties _gpu_property = {};
	
	uint32_t _graphics_family_index=0;
};

