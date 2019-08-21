#pragma once

#include <string>
#include <vector>

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(GLuint slot = 0);
	void Unbind();


	int GetWidth() { return width; }
	int GetHeight() { return height; }

private:
	GLuint rendererID;
	std::string path;
	unsigned char* localBuffer;
	int width, height, BPP;



};

