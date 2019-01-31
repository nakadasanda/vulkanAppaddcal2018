#include "Platform.h"

#include "Renderer.h"
#include "Window.h"
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <sstream>



Renderer::Renderer()
{
	_SetupLayersAndExtensions();
	_InitInstance();
	_InitDevise();
}


Renderer::~Renderer()
{
	_DeInitDevice();
	_DeInitInstance();
}

Window * Renderer::OpenWindow(uint32_t size_x, uint32_t size_y, std::string name)
{
	_window = new Window(this,size_x, size_y, name);
	return _window;
}

bool Renderer::Run()
{
	if (nullptr != _window) {
		return _window->Update();
	}
	return true;
	
}

const VkInstance Renderer::GetVulkanInstance()
{
	return _instance;
}

const VkPhysicalDevice Renderer::GetVulkanPhysicalDevice()
{
	return _gpu;
}

const VkDevice Renderer::GetVulkanDevice()
{
	return _device;
}

const VkQueue Renderer::GetVulkanQueue()
{
	return _queue;
}

const uint32_t Renderer::GetVulkanQueueFamilyIndex()
{
	return _graphics_family_index;
}

const VkPhysicalDeviceProperties & Renderer::GetVulkanPhysicalDeviceProperties()
{
	return VkPhysicalDeviceProperties();
}
void Renderer::_SetupLayersAndExtensions()
{
	_instance_layers.push_back("VK_LAYER_LUNARG_standard_validation");

	_instance_extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	_instance_extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
}

void printDeviceStatus(VkPhysicalDevice &gpu) {
	VkPhysicalDeviceProperties gpu_properties;
	VkPhysicalDeviceFeatures features_properties;
	VkPhysicalDeviceMemoryProperties memory_properties;

	uint32_t queue_families_count = 0;
	vkGetPhysicalDeviceProperties( gpu,&gpu_properties);
	uint32_t apiVer = gpu_properties.apiVersion;

	std::cout << "gpu_Properties" << std::endl;
	std::cout << std::endl;
	std::cout << "Name:\t" << gpu_properties.deviceName << std::endl;
	std::cout << "API Version:\t" << VK_VERSION_MAJOR(apiVer) << "." <<VK_VERSION_MINOR(apiVer) << "." <<VK_VERSION_PATCH(apiVer) << std::endl;
	std::cout << "Driver Version:\t" << gpu_properties.driverVersion << std::endl;
	std::cout << "Vendor ID:\t" << gpu_properties.vendorID << std::endl;
	std::cout << "Device ID:\t" << gpu_properties.deviceID << std::endl;
	std::cout << "Device Type:\t" << gpu_properties.deviceType << std::endl;

	std::cout << std::endl;

	vkGetPhysicalDeviceFeatures(gpu, &features_properties);
	vkGetPhysicalDeviceMemoryProperties(gpu, &memory_properties);
	

	
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_families_count, nullptr);
	std::vector<VkQueueFamilyProperties> family_property(queue_families_count);
	std::cout << "QueufamilyCount:\t" << queue_families_count << std::endl;
	std::cout << std::endl;

	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_families_count, family_property.data());
	std::cout << "QueueFamilyProperties" << std::endl;
	std::cout << std::endl;
	for (uint32_t i = 0; i <queue_families_count; ++i){
		std::cout << std::endl;
		std::cout << "Queue Family #" << i << std::endl;
		std::cout << "VK_QUEUE_GRAPHICS_BIT:\t" << ((family_property[i].queueFlags &VK_QUEUE_GRAPHICS_BIT) != 0) << std::endl;
		std::cout << "&VK_QUEUE_COMPUTE_BIT:\t" << ((family_property[i].queueFlags &VK_QUEUE_COMPUTE_BIT) != 0) << std::endl;
		std::cout << "VK_QUEUE_TRANSFER_BIT:\t" << ((family_property[i].queueFlags &VK_QUEUE_TRANSFER_BIT) != 0) << std::endl;
		std::cout << "VK_QUEUE_SPARSE_BINDING_BIT:\t" << ((family_property[i].queueFlags &VK_QUEUE_SPARSE_BINDING_BIT) != 0) << std::endl;
		std::cout << "QUEUE COUNT:\t" << family_property[i].queueCount << std::endl;
		std::cout << "timestampValidBits:\t" << family_property[i].timestampValidBits << std::endl;
		uint32_t width = family_property[i].minImageTransferGranularity.width;
		uint32_t height = family_property[i].minImageTransferGranularity.height;
		uint32_t depth = family_property[i].minImageTransferGranularity.depth;
		std::cout << "minImageTransferGranularity:\t" << width << ", "<< height<<", " << depth << std::endl;

	}

	uint32_t extensions_count = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, nullptr);
	std::vector<VkExtensionProperties> extensions(extensions_count);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, extensions.data());

	std::cout << std::endl;
	std::cout << "Amount of Extensions " << extensions_count << std::endl;
	std::cout << std::endl;
	std::cout << "ExtensionProperties" << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < extensions_count; i++) {
		std::cout << std::endl;
		std::cout << "Name:        " << extensions[i].extensionName << std::endl;
		std::cout << "specVersion: " << extensions[i].specVersion << std::endl;

	}
	std::cout << std::endl;
	
	uint32_t layer_count = 0;
	vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

	std::vector<VkLayerProperties> layers(layer_count);

	vkEnumerateInstanceLayerProperties(&layer_count, layers.data());

	std::cout << "Amount of Layers " << layer_count << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < layer_count; i++) {
		std::cout << std::endl;
		std::cout << "layerName:            " << layers[i].layerName << std::endl;
		std::cout << "specVersion:          " << layers[i].specVersion << std::endl;
		std::cout << "implementationVersion:" << layers[i].implementationVersion << std::endl;
		std::cout << "description:          " << layers[i].description << std::endl;
	}

	std::cout << std::endl;
}



void Renderer::_InitInstance()
{
	VkApplicationInfo application_info{};
	application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	application_info.apiVersion = VK_MAKE_VERSION(1, 0, 3);
	application_info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	application_info.pApplicationName = "VulkanAppAdcal2018";

	VkInstanceCreateInfo instance_create_info{};
	instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_create_info.pNext = nullptr;
	instance_create_info.flags = 0;
	instance_create_info.pApplicationInfo = &application_info;
	instance_create_info.enabledExtensionCount = _instance_layers.size();
	instance_create_info.ppEnabledLayerNames = _instance_layers.data();
	instance_create_info.enabledExtensionCount = _instance_extensions.size();
	instance_create_info.ppEnabledExtensionNames = _instance_extensions.data();

	auto err = vkCreateInstance(&instance_create_info, nullptr, &_instance);
	if (VK_SUCCESS != err) {
		assert(0 && "Vulkan ERROR: Create instance failed!!");
		std::exit(-1);
	}
}




void Renderer::_InitDevise()
{
	uint32_t gpu_count = 0;
	vkEnumeratePhysicalDevices(_instance, &gpu_count, nullptr);
	std::vector<VkPhysicalDevice> gpu_list(gpu_count);
	std::cout << "gpu_count = "<< gpu_count <<std::endl;
	std::cout << std::endl;
	vkEnumeratePhysicalDevices(_instance, &gpu_count, gpu_list.data());
	_gpu = gpu_list[0]; 

	float queue_priorities[]{ 1.0f};
	VkDeviceQueueCreateInfo device_queue_create_info{};
	device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	device_queue_create_info.queueFamilyIndex = 0;
	device_queue_create_info.queueCount = 1; 
	device_queue_create_info.pQueuePriorities = queue_priorities;

	VkDeviceCreateInfo device_create_info{};
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.queueCreateInfoCount = 1;
	device_create_info.pQueueCreateInfos = &device_queue_create_info;


	auto err = vkCreateDevice(_gpu, &device_create_info, nullptr, &_device);
	if (VK_SUCCESS != err) {
		assert(0 && "Vulkan Err :Device Create failed");
		std::exit(-1);
	}
	printDeviceStatus(_gpu);

	vkDeviceWaitIdle(_device);
	
	vkGetDeviceQueue(_device, 0, 0, &_queue);

}

void Renderer::_DeInitInstance()
{
	vkDestroyInstance(_instance, nullptr);
	_instance = nullptr;

}

void Renderer::_DeInitDevice()
{
	vkDestroyDevice(_device, nullptr);
	_device = nullptr;

}