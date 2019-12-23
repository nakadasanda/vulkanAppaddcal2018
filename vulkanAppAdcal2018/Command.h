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
	VkDevice _device;

};