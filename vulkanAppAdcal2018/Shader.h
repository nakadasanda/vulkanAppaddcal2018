#pragma once
#include "Renderer.h"

#include <fstream>
#include <filesystem>



class Shader
{
public:
	Shader(Renderer * renderer);
	~Shader();
	const VkShaderModule GetVulkanVertShaderModule();
	const VkShaderModule GetVulkanFragShaderModule();
private:
	void create_shaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
	void _init_shaderModule();
	
	std::vector<char> ReadFile(const std::string& filename);
	size_t GetfileSize(std::string filename);

	Renderer* _renderer = nullptr;
	VkDevice _device;
	VkShaderModule _shaderModuleVert;
	VkShaderModule _shaderModuleFrag;
	std::vector<char> _VertShader;
	std::vector<char> _FragShader;
};