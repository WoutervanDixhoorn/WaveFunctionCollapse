#pragma once
#include <stdint.h>
#include <map>
#include <utility>

#include "Buffer.h"
#include "Shader.h"
#include "Texture2D.h"

#include <glm.hpp>

namespace Douter {

	class TextureHandler
	{
	private:
		std::map<Texture2D*, int>* m_TextureMap;
		int m_CurrentSlot;
		int m_SlotCount;

	public:
		TextureHandler()
		{
			m_TextureMap = new std::map<Texture2D*, int>();
			m_CurrentSlot = 0;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_SlotCount);
		}

		void Add(Texture2D& texture)
		{
			if(m_TextureMap->find(&texture) == m_TextureMap->end())
				m_TextureMap->insert(std::pair<Texture2D*, int>(&texture, m_CurrentSlot++));
		}

		int Bind(Texture2D& texture)
		{
			Add(texture);
			int slot = m_TextureMap->find(&texture)->second;
			texture.Bind(slot);
			return slot;
		}
	};
	
	struct QuadVertex
	{
		glm::vec3 m_Position;
		glm::vec2 m_TexCoord;
		glm::vec4 m_Color;
	};

	struct RendererData
	{
		int m_MaxQuads = 1000;
		int m_MaxVertices = 4 * m_MaxQuads;
		int m_MaxIndices = 6 * m_MaxQuads;
		int m_VertexCount = 0;
		int m_QuadCount = 0;

		QuadVertex* m_QuadVertices = nullptr;
		QuadVertex* m_CurrentQuadVertex = nullptr;

		Shader* m_BasicShader = nullptr;
		VertexArray* m_QuadVAO = nullptr;
		VertexBuffer* m_QuadVBO = nullptr;
		IndexBuffer* m_QuadIBO = nullptr;

		Texture2D* m_WhiteTexture = nullptr;
	};

	class Renderer2D
	{
	private:
		static RendererData* m_Data;

	public:
		Renderer2D();

		static void Init();

		//Batch Commands
		static void BeginBatch();
		static void EndBatch();
		static void CheckBatch();

		// Draw Primitives
		static void DrawRect(int x, int y, Color color);
		static void DrawRect(int x, int y, Texture2D& texture);

	private:
		static TextureHandler* m_TextureHandler;
	};

}