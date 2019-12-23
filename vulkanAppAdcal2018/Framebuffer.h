#pragma once
#include "Pipeline.h"
#include "Renderer.h"
#include <vector>
#include "Window.h"
class Framebuffer
{
public:
	Framebuffer(Pipeline *pieline,Renderer *render,Window* window);
	~Framebuffer();
	void CreateFramebuffer();
private:
	void DeinitFramebuffer();
	Pipeline *_pipeline = nullptr;
	VkRenderPass _renderPass ;
	VkDevice _device;
	std::vector<VkImageView> _imageview;
	std::vector <VkFramebuffer> framebuffers;
};

