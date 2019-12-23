#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include <string>
#include <assert.h>

class Pipeline;
class Window;
class Shader;
class Command;
class Framebuffer;

class Renderer
{
public:
	Renderer();
	~Renderer();

	Window * OpenWindow(uint32_t size_x,uint32_t size_y,std::string name);
	Shader * CreateShder();
	Pipeline* CreatePipeline();
	Command* CreateCommand();
	VkFramebuffer* CreateFramebuffer();
	bool Run();

	const VkInstance	GetVulkanInstance();
	const VkPhysicalDevice	GetVulkanPhysicalDevice();
	const VkDevice	GetVulkanDevice();
	const VkQueue	GetVulkanQueue();
	const uint32_t	GetVulkanQueueFamilyIndex();
	const VkPhysicalDeviceProperties	& GetVulkanPhysicalDeviceProperties();

private:
	void _SetupLayersAndExtensions();
	void _InitInstance();
	void _DeInitInstance();

	void _InitDevise();
	void _DeInitDevice();

	

	VkInstance	_instance = nullptr;
	VkPhysicalDevice _gpu = nullptr;
	VkDevice	_device = nullptr;
	VkPhysicalDeviceProperties _gpu_property = {};
	VkQueue _queue;
	uint32_t _graphics_family_index = 0;

	Window *_window = nullptr;
	Shader *_shader = nullptr;
	Pipeline* _pipeline = nullptr;
	Command* _command = nullptr;
	Framebuffer* _framebuffer = nullptr;
	std::vector<const char*>	_instance_layers;
	std::vector<const char*>	_instance_extensions;
	std::vector<const char*>	_device_layers;
	std::vector<const char*>	_device_extensions;
	

};

