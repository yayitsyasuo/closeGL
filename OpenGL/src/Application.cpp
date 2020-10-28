#include "Graphics.h"
#include "Window.h"


int main(void)
{
	Window win { 640, 480, "Appreciate this folk" };
	Graphics gfx;
	gfx.init();

	return win.Go();
}