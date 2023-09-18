#include "Texture.hpp"

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <cstdint>
#include <iostream>

Texture::Texture()
{
	uint32_t pixels = 0xffffffff;
	m_Width = 1;
	m_Height = 1;
	m_ChannelCount = 4;
	CreateTextureObject((unsigned char*)&pixels);
}

Texture::Texture(const char* imgPath)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* pixels = stbi_load(imgPath, &m_Width, &m_Height, &m_ChannelCount, 0);
	if (pixels)
	{
		CreateTextureObject(pixels);
		stbi_image_free(pixels);
	}
	else
	{
		std::cout	<< "Failed to load image resource!" << std::endl
					<< "File: " << imgPath << std::endl;
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture::Activate() const
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::CreateTextureObject(unsigned char* pixels)
{
	// Create and bind texture objects
	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	Activate();

	// Texture Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// Trilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				// Bilinear filtering

	// Upload image data to the OpenGL
	glTexImage2D(	GL_TEXTURE_2D, 
					0, 
					GL_RGBA, 
					m_Width, m_Height, 
					NULL, 
					m_ChannelCount == 1 ? GL_RED : m_ChannelCount == 2 ? GL_RG : m_ChannelCount == 3 ? GL_RGB : GL_RGBA,
					GL_UNSIGNED_BYTE,
					pixels);

	// Generate mipmap for uploaded texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}
