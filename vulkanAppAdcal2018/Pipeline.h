#pragma once
#include "Renderer.h"
#include "Shader.h"

class Shader;
class Renderer;

class Pipeline 
{
public:
	Pipeline(Shader* shader,Renderer* render);
	~Pipeline();
	const VkRenderPass GetrenderPass();
private:
	void CreatePipeline();
	void DeCreatePipeline();

	Shader *_shader = nullptr;
	Renderer* _renderer = nullptr;
	VkShaderModule _shaderModuleVert;
	VkShaderModule _shaderModuleFrag;
	
	VkPipelineLayout _pipelineLayout;
	VkDevice _device;
	VkRenderPass _renderPass;
	VkPipeline _pipeline;
};