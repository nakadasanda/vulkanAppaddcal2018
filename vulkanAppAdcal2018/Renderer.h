#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class Window;

class Renderer
{
public:
	Renderer();
	~Renderer();

	Window * OpenWindow(uint32_t size_x,uint32_t size_y,std::string name);

	bool Run();

//private:
	void _InitInstance();
	void _DeInitInstance();

	void _InitDevise();
	void _DeInitDevice();

	VkInstance	_instance = nullptr;
	VkPhysicalDevice _gpu = nullptr;
	VkDevice	_device = nullptr;
	VkPhysicalDeviceProperties _gpu_property = {};
	
	Window *_window = nullptr;

};

