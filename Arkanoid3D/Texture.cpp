#include "pch.h"
#include "Texture.h"

#include "stb_img/stb_img.h"

#include <iostream>

Texture::Texture(const std::string& filePath):
		rendererID(0)
	,	path(filePath)
	,	localBuffer(nullptr)
	,	width(0)
	,	height(0)
	,	BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

	if (!localBuffer)
		std::cout << "\nTexture loading failed\n";

	glGenTextures(1, &rendererID);
	glBindBuffer(GL_TEXTURE_2D, rendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localBuffer)
		stbi_image_free(localBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &rendererID);
}

void Texture::Bind(GLuint slot)
{
	if (slot > 31)
		return;

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindBuffer(GL_TEXTURE_2D, rendererID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
