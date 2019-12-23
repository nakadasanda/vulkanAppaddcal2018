#pragma once
#include"Renderer.h"
class Command;

class Command {
public:
	Command(Renderer* render);
	~Command();
private:
	void CreateCommandPool();
	VkCommandPool _commandPool;
	std::vector<VkCommandBuffer> _commandbufers;
	VkDevice _device;

};