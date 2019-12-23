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
}

Command::~Command()
{
	vkDestroyCommandPool(_device, _commandPool, nullptr);
}