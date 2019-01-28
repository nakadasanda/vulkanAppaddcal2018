#pragma once
//Windows
#if defined(_WIN32)

#define VK_USE_PLATFORM_WIN32_KHR 0;
#define GLFW_INCLUDE_VULKAN 1;
#include <Windows.h>

#endif

#include <vulkan/vulkan.h>

