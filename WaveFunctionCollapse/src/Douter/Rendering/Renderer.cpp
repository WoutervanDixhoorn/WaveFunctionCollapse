#include "Renderer.h"

#include <glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Douter {

	RendererData* Renderer2D::m_Data = nullptr;
	TextureHandler* Renderer2D::m_TextureHandler = nullptr;

	Renderer2D::Renderer2D()
	{

	}

	void Renderer2D::Init()
	{
		m_Data = new RendererData();
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

		m_Data->m_WhiteTexture = new Texture2D(1, 1, {1.0f, 1.0f, 1.0f});

		m_Data->m_BasicShader = new Shader("res\\shaders\\basic.shader");

		//Change this to viewport size accordingly
		glm::mat4 orthoMatrix = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
		m_Data->m_BasicShader->SetUniform<glm::mat4>("u_Projection", orthoMatrix);
	}

	void Renderer2D::BeginBatch()
	{
		m_Data->m_BasicShader->Bind();
		
		int slot = m_TextureHandler->Bind(*m_Data->m_WhiteTexture); //TODO: Make texture white standard slot 0
		m_Data->m_BasicShader->SetUniform<int>("u_Texture", slot);

		glm::mat4 orthoMatrix = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
		m_Data->m_BasicShader->SetUniform<glm::mat4>("u_Projection", orthoMatrix);


		m_Data->m_CurrentQuadVertex = m_Data->m_QuadVertices;
		m_Data->m_VertexCount = 0;
		m_Data->m_QuadCount = 0;
	}

	void Renderer2D::EndBatch()
	{
		uint32_t dataSize = m_Data->m_QuadCount * sizeof(QuadVertex);
		m_Data->m_QuadVBO->Data(dataSize, m_Data->m_QuadVertices);

		m_Data->m_QuadVAO->Bind();
		int indexCount = m_Data->m_QuadCount * 6;
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}

	void Renderer2D::CheckBatch()
	{
		if (m_Data->m_VertexCount + 4 > m_Data->m_MaxVertices) {
			EndBatch();
			BeginBatch();
		}
	}

	void Renderer2D::DrawRect(int x, int y, Color color)
	{
		CheckBatch();

		int textureSlot = m_TextureHandler->Bind(*m_Data->m_WhiteTexture);

		m_Data->m_CurrentQuadVertex->m_Position = { -0.5f + x, -0.5f + y, 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 0.0f, 0.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { -0.5f + x, 0.5f + y, 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 1.0f, 0.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { -0.5f + x, -0.5f + y, 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 1.0f, 1.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_CurrentQuadVertex->m_Position = { 0.5f + x, -0.5f + y, 0.0f };
		m_Data->m_CurrentQuadVertex->m_TexCoord = { 0.0f, 1.0f };
		m_Data->m_CurrentQuadVertex->m_Color = color;
		m_Data->m_CurrentQuadVertex++;

		m_Data->m_VertexCount += 4;
		m_Data->m_QuadCount++;

		//m_Data->m_BasicShader->Bind();
		//m_Data->m_RectVAO->Bind();

		//m_Data->m_BasicShader->SetUniform<int>("u_Texture", m_TextureHandler->Bind(*m_Data->m_WhiteTexture));
		//m_Data->m_BasicShader->SetUniform<int>("u_TexScale", 1.0f);

		//m_Data->m_BasicShader->SetUniform<glm::vec4>("u_Color", color);

		//glm::mat4 modelMatrix = glm::mat4(1.0f);
		//modelMatrix = glm::translate(modelMatrix, glm::vec3(float(x), float(y), 0.0f));
		//m_Data->m_BasicShader->SetUniform<glm::mat4>("u_Model", modelMatrix);

		//glDrawElements(GL_TRIANGLES, m_Data->m_RectIBO->GetCount(), GL_UNSIGNED_INT, 0);
	}

	void Renderer2D::DrawRect(int x, int y, Texture2D& texture)
	{
		m_Data->m_BasicShader->Bind();
		m_Data->m_QuadVAO->Bind();

		m_Data->m_BasicShader->SetUniform<int>("u_Texture", m_TextureHandler->Bind(*m_Data->m_WhiteTexture));
		m_Data->m_BasicShader->SetUniform<float>("u_Tilling", 1.0f);

		m_Data->m_BasicShader->SetUniform<glm::vec4>("u_Color", {1.0f, 1.0f, 1.0f, 1.0f});

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(float(x), float(y), 0.0f));
		m_Data->m_BasicShader->SetUniform<glm::mat4>("u_Model", modelMatrix);

		glDrawElements(GL_TRIANGLES, m_Data->m_QuadIBO->GetCount(), GL_UNSIGNED_INT, 0);
	}

}