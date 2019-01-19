#include "Window.h"



Window::Window(uint32_t size_x, uint32_t size_y, std::string name)
{
	_surface_size_x = size_x;
	_surface_size_x = size_y;
	_window_name = name;
	_InitWindow();
}



Window::~Window()
{
	_DeInitWindow();
}

void Window::Close()
{
	_window_should_run = false;
}

bool Window::Update()
{
	_UpdateWindow();
	return _window_should_run;
}
