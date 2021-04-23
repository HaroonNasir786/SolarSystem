#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

class Texture
{
public:

	Texture();
	~Texture();

	bool Load(char* path, int width, int height);

	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }


private:

	GLuint _ID; //Texture ID
	int _width, _height;
};

