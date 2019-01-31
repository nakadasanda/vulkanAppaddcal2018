#pragma once

#include "Platform.h"

#include "Renderer.h"
#include <GLFW\glfw3.h>
#include <String>

class Window
{
public:
	Window(Renderer * renderer, uint32_t size_x, uint32_t size_y, std::string name);
	~Window();

	void Close();
	bool Update();
	

private:
	void _InitOSWindow();
	void _DeInitOSWindow();
	void _UpdateOSWindow();
	void _InitOSSurface();

	void _InitSurface();
	void _DeInitSurface();
	Renderer * _renderer = nullptr;

	VkSurfaceKHR _surface = VK_NULL_HANDLE;
	uint32_t	_surface_size_x = 520;
	uint32_t	_surface_size_y = 520;
	std::string _window_name;

	GLFWwindow *_GLFW_window;

	VkSurfaceFormatKHR _surface_format = {};
	VkSurfaceCapabilitiesKHR _surface_capabilities = {};
	
	bool _window_should_run = true;

#if VK_USE_PLATFORM_WIN32_KHR
	HINSTANCE	_win32_instance = NULL;
	HWND	_win32_window = NULL;
	std::string	_win32_class_name;
	static	uint64_t	_win32_class_id_counter;

#elif GLFW_INCLUDE_VULKAN
#endif

};
