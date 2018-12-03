#include "Renderer.h"

#include  <cstdlib>
#include <assert.h>
#include <vector>

Renderer::Renderer()
{
	_InitInstance();
	_InitDevise();
}


Renderer::~Renderer()
{
	_DeInitDevice();
	_DeInitInstance();

	system("pause");
}

void Renderer::_InitInstance()
{
	VkApplicationInfo application_info{};
	application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	application_info.apiVersion = VK_API_VERSION_1_0;
	application_info.pApplicationName = "VulkanAppAdcal2018";

	VkInstanceCreateInfo instance_create_info{};
	instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_create_info.pApplicationInfo = &application_info;
	auto err = vkCreateInstance(&instance_create_info, nullptr, &_instance);
	if (VK_SUCCESS != err) {
		assert(0 && "Vulkan ERROR: Create instance failed!!");
		std::exit(-1);
	}
}

void Renderer::_DeInitInstance()
{
	vkDestroyInstance(_instance, nullptr);
	_instance = nullptr;
}

void Renderer::_InitDevise()
{
	{
		uint32_t gpu_count = 0;
		vkEnumeratePhysicalDevices(_instance, &gpu_count, nullptr);
		std::vector<VkPhysicalDevice> gpu_list(gpu_count);
		vkEnumeratePhysicalDevices(_instance, &gpu_count, gpu_list.data());
		_gpu = gpu_list[0];
		vkGetPhysicalDeviceProperties(_gpu, &_gpu_property);
	}
	{
		uint32_t family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(_gpu,&family_count,nullptr);
		std::vector<VkQueueFamilyProperties> family_property_list(family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &family_count, family_property_list.data());

		bool found = false;
		for (uint32_t i = 0; i < family_count; ++i) {
			if (family_property_list[i].queueFlags  & VK_QUEUE_GRAPHICS_BIT) {
				found = true;
				_graphics_family_index = 1;
			}
		}
		if (!found) {
			assert(0 && "Vulkan err: Queue Family supporting graphics not faound");
		std:exit(-1);
		}
	}
	float queue_priorities[]{1.0f};
	VkDeviceQueueCreateInfo device_queue_create_info{};
	device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	device_queue_create_info.queueFamilyIndex = _graphics_family_index;
	device_queue_create_info.queueCount = 1;
	device_queue_create_info.pQueuePriorities = queue_priorities;

	VkDeviceCreateInfo device_create_info{};
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.queueCreateInfoCount = 1;
	device_create_info.pQueueCreateInfos = &device_queue_create_info;
	auto err = vkCreateDevice(_gpu, &device_create_info, nullptr, &_devise);
	if (VK_SUCCESS != err) {
		assert(0 && "Vulkan Err :Device Create failed");
		std::exit(-1);
	}
}

void Renderer::_DeInitDevice()
{
	vkDestroyDevice(_devise, nullptr);
	_devise = nullptr;
}
