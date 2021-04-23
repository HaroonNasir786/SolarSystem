#pragma once
#define REFRESHRATE 16
#include <Windows.h> //Required for OpenGL on Windows 
#include <gl/GL.h> //OpenGL 
#include <gl/GLU.h> //OpenGL Utilities 
#include "GL\freeglut.h" //freeglut library
#include <math.h>
#include "Structures.h"
#include <time.h>
#include "GLUTCallBacks.h"
class Texture;

class SolarSystem
{
public:

	SolarSystem(int argc, char* argv[]);
	void InitGL(int argc, char* argv[]);
	~SolarSystem();

	void Render();
	void ResizePlanets(int w, int h);
	void Setup();
	void Idle();

	void Keyboard(unsigned char key, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);
	void StarCoordinates(point* stars);
	void DrawStars();
	void Menu(const char* str, float size);
	void LoadTexture();
	void LoadPlanets();

 private:

	 float first = 1;
	 float second = 1;
	 float rotation = 0.0;
	 bool animation = false;
	 float tx = 0.0;
	 float worldX = 15.0;
	 float worldY = 0.0;
	 float scaleFactor = 0.6;
	 int globalW, globalH;
	 point stars[500];

	 Texture* sunTex;
	 Texture* earthTex;
	 Texture* marsTex;
	 Texture* jupitarTex;
	 Texture* uranusTex;
	 Texture* neptuneTex;
	 Texture* plutoTex;
	 Texture* mercuryTex;

};

