#include "../Application.h"
#include "Renderer.h"

#include <glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Douter {

	RendererData* Renderer2D::m_Data = nullptr;
	RendererStats* Renderer2D::m_Stats = nullptr;
	TextureHandler* Renderer2D::m_TextureHandler = nullptr;

	Renderer2D::Renderer2D()
	{
	}

	void Renderer2D::Init()
	{
		m_Data = new RendererData();
		m_Stats = new RendererStats(); m_Stats->m_Timer = Timer();
		m_TextureHandler = new TextureHandler();

		m_Data->m_QuadVBO = new VertexBuffer(m_Data->m_MaxVertices * sizeof(QuadVertex));
		m_Data->m_QuadVertices = new QuadVertex[m_Data->m_MaxVertices];

		unsigned int* quadIndices = new unsigned int[m_Data->m_MaxIndices];

		int offset = 0;
		for (int i = 0; i < m_Data->m_MaxIndices; i += 6)
		{
			quadIndices[i] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 0;
			quadIndices[i + 4] = offset + 2;
			quadIndices[i + 5] = offset + 3;

			offset += 4;
		}

		m_Data->m_QuadIBO = new IndexBuffer(m_Data->m_MaxIndices * sizeof(unsigned int), m_Data->m_MaxIndices, quadIndices);
		delete[] quadIndices;

		m_Data->m_QuadVAO = new VertexArray();
		m_Data->m_QuadVAO->AddBuffer(m_Data->m_QuadVBO);
		m_Data->m_QuadVAO->AddBuffer(m_Data->m_QuadIBO);
		m_Data->m_QuadVAO->Add<float>(3);//m_Position
		m_Data->m_QuadVAO->Add<float>(2);//m_TexCoord
		m_Data->m_QuadVAO->Add<float>(4);//m_Color
		m_Data->m_QuadVAO->Add<float>(1);//m_TexIndex
		m_Data->m_QuadVAO->Add<float>(1);//m_Tilling

		m_Data->m_WhiteTexture = new Texture2D(1, 1, {1.0f, 1.0f, 1.0f});

		m_Data->m_BasicShader = new Shader("res\\shaders\\basic.shader");

		//TODO: Fix function that does this automatically
		unsigned int uLocation = glGetUniformLocation(m_Data->m_BasicShader->GetID(), "u_Textures");
		int* samplers = new int[m_TextureHandler->MaxSlots];
		for (int i = 0; i < m_TextureHandler->MaxSlots; i++) samplers[i] = i;
		glUniform1iv(uLocation, 6, samplers);
	}

	void Renderer2D::BeginBatch(bool resetStats)
	{
		//Reset stats
		if (resetStats) {
			m_Stats->m_DrawCalls = 0;
			m_Stats->m_VertexCount = 0;
			m_Stats->m_QuadCount = 0;
		}


		m_Data->m_BasicShader->Bind();

		glm::mat4 viewProj = Application::Get().GetActiveCamera().GetViewProjection(); //TODO: Correct this with viewport size
		m_Data->m_BasicShader->SetUniform<glm::mat4>("u_ViewProjection", viewProj);

		m_Data->m_CurrentQuadVertex = m_Data->m_QuadVertices;
		m_Data->m_VertexCount = 0;
		m_Data->m_QuadCount = 0;
	}

	void Renderer2D::EndBatch()
	{
		uint32_t dataSize = m_Data->m_VertexCount * sizeof(QuadVertex);
		m_Data->m_QuadVBO->Data(dataSize, m_Data->m_QuadVertices);

		m_Data->m_QuadVAO->Bind();
		int indexCount = m_Data->m_QuadCount * 6;
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		
		//Update Renderer Stats
		m_Stats->m_DrawCalls += 1;
	}

	void Renderer2D::CheckBatch()
	{
		if (m_TextureHandler->GetBound() > m_TextureHandler->MaxSlots)
		{
			EndBatch();
			m_TextureHandler->Reset();
			BeginBatch(false);
		}else if(m_Data->m_VertexCount + 4 > m_Data->m_MaxVertices)
		{
			EndBatch();
			BeginBatch(false);
		}
	}

	void Renderer2D::DrawRect(float x, float y, float sizeX, float sizeY, Color color)
	{
		CheckBatch();

		int textureSlot = m_TextureHandler->Bind(*m_Data->m_WhiteTexture);
		float tilling = 1.0f;

		m_Data->m_CurrentQuadVertex->m_Position = { x - (sizeX / 2), y - (sizeY / 2), 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 0.0f, 0.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex->m_TexIndex = textureSlot;
		m_Data->m_CurrentQuadVertex->m_TillingFactor = tilling;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { x - (sizeX / 2), y + sizeY - (sizeY / 2), 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 0.0f, 1.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex->m_TexIndex = textureSlot;
		m_Data->m_CurrentQuadVertex->m_TillingFactor = tilling;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { x + sizeX - (sizeX / 2), y + sizeY - (sizeY / 2), 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 1.0f, 1.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex->m_TexIndex = textureSlot;
		m_Data->m_CurrentQuadVertex->m_TillingFactor = tilling;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { x + sizeX - (sizeX / 2), y - (sizeY / 2), 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 1.0f, 0.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex->m_TexIndex = textureSlot;
		m_Data->m_CurrentQuadVertex->m_TillingFactor = tilling;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_VertexCount += 4;
		m_Data->m_QuadCount++;

		//Update stats
		m_Stats->m_VertexCount += 4;
		m_Stats->m_QuadCount += 1;
	}

	void Renderer2D::DrawRect(float x, float y, float sizeX, float sizeY, Texture2D& texture, float tilling /*=0*/)
	{
		CheckBatch();

		Color color = { 1.0f, 1.0f, 1.0f };
		int textureSlot = m_TextureHandler->Bind(texture);

		m_Data->m_CurrentQuadVertex->m_Position = { x - (sizeX/2) , y - (sizeY / 2), 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 0.0f, 0.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex->m_TexIndex = textureSlot;
		m_Data->m_CurrentQuadVertex->m_TillingFactor = tilling;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { x - (sizeX / 2), y + sizeY - (sizeY / 2), 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 0.0f, 1.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex->m_TexIndex = textureSlot;
		m_Data->m_CurrentQuadVertex->m_TillingFactor = tilling;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { x + sizeX - (sizeX / 2), y + sizeY - (sizeY / 2), 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 1.0f, 1.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex->m_TexIndex = textureSlot;
		m_Data->m_CurrentQuadVertex->m_TillingFactor = tilling;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { x + sizeX - (sizeX / 2), y - (sizeY / 2), 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 1.0f, 0.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex->m_TexIndex = textureSlot;
		m_Data->m_CurrentQuadVertex->m_TillingFactor = tilling;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_VertexCount += 4;
		m_Data->m_QuadCount++;

		//Update stats
		m_Stats->m_VertexCount += 4;
		m_Stats->m_QuadCount += 1;
	}

}