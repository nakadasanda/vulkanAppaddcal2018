#include "Shader.h"
#include <assert.h>


Shader::Shader(Renderer *renderer) {
	_renderer = renderer;
	_device = _renderer->GetVulkanDevice();

	_init_shaderModule();
}

Shader::~Shader() {
	vkDestroyShaderModule(_device, _shaderModuleVert, nullptr);
	vkDestroyShaderModule(_device, _shaderModuleFrag, nullptr);
}

const VkShaderModule Shader::GetVulkanVertShaderModule()
{
	return _shaderModuleVert;
}

const VkShaderModule Shader::GetVulkanFragShaderModule()
{
	return _shaderModuleFrag;
}

std::vector<char> Shader::ReadFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("Don't read" + filename);
	}
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> fileBuffer(fileSize);
	file.seekg(0);
	file.read(fileBuffer.data(), fileSize);
	file.close();
	return fileBuffer;
}

size_t Shader::GetfileSize(std::string filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open()) {
		throw std::runtime_error("Don't read" + filename );
	}
	size_t fileSize = (size_t)file.tellg();
	file.close();
	return fileSize;
}

void Shader::create_shaderModule(const std::vector<char>& code, VkShaderModule *shaderModule )
{
	 

	VkShaderModuleCreateInfo shaderCreateInfo;
	shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderCreateInfo.pNext = nullptr;
	shaderCreateInfo.flags = 0;
	shaderCreateInfo.codeSize = code.size();
	shaderCreateInfo.pCode = (uint32_t*)code.data();

	VkResult err = vkCreateShaderModule(_device, &shaderCreateInfo, nullptr, shaderModule);
	if (VK_SUCCESS != err) {
		assert(0 && "Vulkan ERROR: Create ShaderModule failed!!");
		std::exit(-1);
	}
}

void Shader::_init_shaderModule()
{
	size_t fileSize = GetfileSize("vert.spv");
	_VertShader.resize(fileSize);
	_VertShader = ReadFile("vert.spv");
	std::cout << "VertShader Size " << fileSize << std::endl;

	fileSize = GetfileSize("frag.spv");
	_FragShader.resize(fileSize);
	_FragShader = ReadFile("frag.spv");
	std::cout << "FragShader Size " << fileSize << std::endl;

	create_shaderModule(_VertShader, &_shaderModuleVert);
	create_shaderModule(_FragShader, &_shaderModuleFrag);
}


