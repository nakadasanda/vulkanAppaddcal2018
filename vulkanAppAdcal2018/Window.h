#pragma once

#include "Platform.h"

#include <GLFW\glfw3.h>
#include <String>

class Window
{
public:
	Window(uint32_t size_x, uint32_t size_y, std::string name);
	~Window();

	void Close();
	bool Update();
	

private:
	void _InitWindow();
	void _DeInitWindow();
	void _UpdateWindow();
	void _Init_Surface();

	uint32_t	_surface_size_x = 520;
	uint32_t	_surface_size_y = 520;
	std::string _window_name;

	GLFWwindow *_GLFW_window;

	bool _window_should_run = true;

#if VK_USE_PLATFORM_WIN32_KHR
	HINSTANCE	_win32_instance = NULL;
	HWND	_win32_window = NULL;
	std::string	_win32_class_name;
	static	uint64_t	_win32_class_id_counter;

#endif

};

