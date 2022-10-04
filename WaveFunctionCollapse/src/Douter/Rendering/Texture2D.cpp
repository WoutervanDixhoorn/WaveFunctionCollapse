#include "Texture2D.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Douter
{

	Texture2D::Texture2D(const std::string filePath) 
		: m_Id(0), m_FilePath(filePath), m_ImageBuffer(nullptr),
		m_Width(0), m_Height(0), m_BPP(0)
	{
		
		stbi_set_flip_vertically_on_load(1);
		m_ImageBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_Width, m_Height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_BGRA, GL_UNSIGNED_BYTE, m_ImageBuffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (m_ImageBuffer)
			stbi_image_free(m_ImageBuffer);
	}

	Texture2D::Texture2D(int width, int height, Color color)
		: m_Id(0), m_FilePath(""), m_ImageBuffer(nullptr),
		m_Width(width), m_Height(height), m_BPP(0)
	{

		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		GenerateImageData(color);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_Id);
	}

	void Texture2D::Bind(unsigned int Slot /*= 0*/)
	{
		//glActiveTexture(GL_TEXTURE0 + Slot);
		//glBindTexture(GL_TEXTURE_2D, m_Id);
		glBindTextureUnit(Slot, m_Id);
	}

	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void Texture2D::GenerateImageData(Color color)
	{
		int format = 4; //rgba or rgb
		const int size = m_Width * m_Height * format;
		unsigned char* imageData = new unsigned char[size];
		memset(imageData, (uint32_t)color, size);

		m_ImageBuffer = imageData;
	}
}