#include "GLUTCallBacks.h"
#include "SolarSystem.h"

// Namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		// Initialise to a null pointer before we do anything
		SolarSystem* Solarsystem = nullptr;
	}

	void Init(SolarSystem* gl)
	{
		Solarsystem = gl;
	}

	void Render()
	{

		if (Solarsystem != nullptr)
		{
			Solarsystem->Render();

		}

	}

	void ResizePlanets(int w, int h)
	{
		if (Solarsystem != nullptr)
		{
			Solarsystem->ResizePlanets(w, h);

		}
	}

	void Idle()
	{
		if (Solarsystem != nullptr)
		{
			Solarsystem->Idle();

		}
	}

	void Keyboard(unsigned char key, int x, int y)
	{

		if (Solarsystem != nullptr)
		{
			Solarsystem->Keyboard(key, x, y);

		}

	}

	void MouseWheel(int button, int dir, int x, int y)
	{
		if (Solarsystem != nullptr)
		{
			Solarsystem->MouseWheel(button, dir, x, y);

		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		Solarsystem->Render();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;

		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);

	}
}