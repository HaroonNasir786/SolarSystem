#include "Texture.h"
#include <iostream>
#include <fstream>
using namespace std;

Texture::Texture()
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &_ID);
}

bool Texture::Load(char* path, int width, int height)
{
	char* tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open tecture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); // seek to end of file
	fileSize = (int)inFile.tellg(); // Get current postion in the file - The End, ths gives us total file size
	tempTextureData = new char[fileSize]; //Create an new aray to store data
	inFile.seekg(0, ios::beg); //Seek back to beginning of file
	inFile.read(tempTextureData, fileSize); // Read in all the datat in one go
	inFile.close(); // Close the file

	cout << path << " loaded. " << endl;

	glGenTextures(1, &_ID); //Get next Texture ID
	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	delete[] tempTextureData; //clear up tje data we dont need anymore

	return true;

}
