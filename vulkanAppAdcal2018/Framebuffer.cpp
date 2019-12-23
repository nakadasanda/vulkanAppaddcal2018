#include "Framebuffer.h"


Framebuffer::Framebuffer(Pipeline *pipeline,Renderer *render,Window* window)
{
	_pipeline = pipeline;
	_renderPass = _pipeline->GetrenderPass();
	_device = render->GetVulkanDevice();
	_imageview = window->GetImageview();
	CreateFramebuffer();
}

Framebuffer::~Framebuffer()
{
	DeinitFramebuffer();
}

void Framebuffer::CreateFramebuffer()
{
	framebuffers.resize(2);

	for (size_t i = 0; i < 2; i++) {
		VkFramebufferCreateInfo framebufferCreateinfo[2];
		framebufferCreateinfo[i].sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateinfo[i].pNext = nullptr;
		framebufferCreateinfo[i].flags = 0;
		framebufferCreateinfo[i].renderPass = _renderPass;
		framebufferCreateinfo[i].attachmentCount = 1;
		framebufferCreateinfo[i].pAttachments = &(_imageview[i]);
		framebufferCreateinfo[i].width = 600;
		framebufferCreateinfo[i].height = 800;
		framebufferCreateinfo[i].layers = 1;

		vkCreateFramebuffer(_device, &framebufferCreateinfo[i], nullptr, &framebuffers[i]);

	}
}
void Framebuffer::DeinitFramebuffer()
{
	for (int i = 0; i < 2; i++) {
		vkDestroyFramebuffer(_device, framebuffers[i], nullptr);
	}
}

