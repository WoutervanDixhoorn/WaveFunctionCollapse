#pragma once
#include <stdint.h>
#include <map>
#include <utility>

#include "../Util.h"
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
		int MaxSlots;

	public:
		TextureHandler()
		{
			m_TextureMap = new std::map<Texture2D*, int>();
			m_CurrentSlot = 0;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_SlotCount);
			MaxSlots = m_SlotCount;
		}

		void Reset()
		{
			m_TextureMap->clear();
			m_CurrentSlot = 0;
		}

		int Add(Texture2D& texture)
		{
			if (m_CurrentSlot >= m_SlotCount)
				return -1;

			if (m_TextureMap->find(&texture) == m_TextureMap->end())
				m_TextureMap->insert(std::pair<Texture2D*, int>(&texture, m_CurrentSlot++));

			return 1;
		}

		int Bind(Texture2D& texture)
		{
			if (Add(texture)) {
				int slot = m_TextureMap->find(&texture)->second;
				texture.Bind(slot);
				return slot;
			}
			return -1;
		}

		int GetBound()
		{
			return m_CurrentSlot;
		}
	};
	
	struct QuadVertex
	{
		glm::vec3 m_Position;
		glm::vec2 m_TexCoord;
		glm::vec4 m_Color;
		float m_TexIndex;
		float m_TillingFactor;
	};

	struct RendererStats
	{
		int m_DrawCalls = 0;
		int m_VertexCount = 0;
		int m_QuadCount = 0;
		
		Timer m_Timer;
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
		static RendererStats* m_Stats;

	public:
		Renderer2D();

		static void Init();

		//Batch Commands
		static void BeginBatch(bool resetStats = true);
		static void EndBatch();
		static void CheckBatch();
		static inline RendererStats* GetStats() { return m_Stats; }

		// Draw Primitives
		static void DrawRect(float x, float y, float sizeX, float sizeY, Color color);
		static void DrawRect(float x, float y, float sizeX, float sizeY, Texture2D& texture, float tilling = 1.0f);

	private:
		static TextureHandler* m_TextureHandler;
	};

}