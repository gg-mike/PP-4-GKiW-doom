#include "pch.h"
#include "Texture.h"

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

Texture::Texture(const std::string& filePath, std::vector<unsigned char> image, uint32_t width, uint32_t height)
	: path(filePath), width(width), height(height)
{
	glGenTextures(1, &textureId); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, textureId); //Uaktywnij uchwyt
	//Wczytaj obrazek do pami�ci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}