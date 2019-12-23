#include "Command.h"


Command::Command(Renderer* render)
{
	_device = render->GetVulkanDevice();
}

void Command::CreateCommandPool()
{
	VkCommandPoolCreateInfo commandPoolCreateInfo;
	commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCreateInfo.pNext = nullptr;
	commandPoolCreateInfo.flags = 0;
	commandPoolCreateInfo.queueFamilyIndex = 0;

	auto err = vkCreateCommandPool(_device, &commandPoolCreateInfo, nullptr, &_commandPool);;
	if (VK_SUCCESS != err) {
		assert(0 && "Vulkan ERROR: Create Pipeline failed!!");
		std::exit(-1);
	}

	VkCommandBufferAllocateInfo commandBufferAllocateInfo;
	commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocateInfo.pNext = nullptr;
	commandBufferAllocateInfo.commandPool = _commandPool;
	commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferAllocateInfo.commandBufferCount = 2;

	_commandbufers.resize(2);
	vkAllocateCommandBuffers(_device, &commandBufferAllocateInfo, _commandbufers.data());
}

Command::~Command()
{
	vkDestroyCommandPool(_device, _commandPool, nullptr);
}