#include "Renderer.h"

int main()
{
	Renderer r;
	r.OpenWindow(800, 600, "vulkan tutorial");
	r.CreateShder();
	while (r.Run()) {

	}
}