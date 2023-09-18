#pragma once

class Texture
{
public:
	Texture();
	Texture(const char* imgPath);
	~Texture();
	unsigned int GetRendererID() const { return m_TextureID; }

	void Activate() const;
private:
	void CreateTextureObject(unsigned char* pixels);
public:
	int pixelPerUnit = 100;
private:
	unsigned int m_TextureID = 0;
	int m_Width = 0;
	int m_Height = 0;
	int m_ChannelCount = 0;
};
