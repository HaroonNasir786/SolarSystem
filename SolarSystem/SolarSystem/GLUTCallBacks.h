#pragma once
class SolarSystem;

namespace GLUTCallbacks
{
	void Init(SolarSystem* gl);
	void Render();
	void ResizePlanets(int w, int h);
	void Idle();
	void Keyboard(unsigned char key, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);
	void Timer(int preferredRefresh);
}


