#pragma once

#include <string>
#include <glm.hpp>

namespace Douter
{
	struct Color
	{
		float r, g, b;

		operator glm::vec4() const
		{
			return glm::vec4(r, g, b, 1.0f);
		}

		operator unsigned int() const
		{
			uint8_t A = 255;
			uint8_t R = 255 * r;
			uint8_t G = 255 * g;
			uint8_t B = 255 * b;
			unsigned int color = (A << 24) + (R << 16) + (G << 8) + B;
			return color;
		}
	};

	class Texture2D
	{
	private:	
		unsigned int m_Id;
		std::string m_FilePath;
		unsigned char* m_ImageBuffer;
		int m_Width, m_Height, m_BPP;


		template <typename T> friend class std::hash;
	public:

		Texture2D(std::string filePath);
		Texture2D(int width, int height, Color color);

		~Texture2D();

		void Bind(unsigned int	Slot = 0);
		void Unbind();

	private:
		void GenerateImageData(Color color);
	};

};

namespace std {

	template<>
	struct hash<Douter::Texture2D>
	{
		size_t operator()(const Douter::Texture2D& key)
		{
			return hash<int>()(key.m_Id);
		}
	};

}