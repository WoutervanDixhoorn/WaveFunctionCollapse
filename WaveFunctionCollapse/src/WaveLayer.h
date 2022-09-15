#pragma once
#include "Douter/ILayer.h"
#include "Douter/Rendering/Buffer.h"
#include "Douter/Rendering/Shader.h"

#include "imgui.h"
#include "glad/glad.h"

class WaveLayer : public Douter::ILayer
{
private:
	float vertices[12] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	Douter::VertexBuffer* VBO;
	Douter::VertexArray* VAO;
	Douter::Shader* shader;

public:

	virtual void OnAttach()
	{
		shader = new Douter::Shader("res\\shaders\\basic.shader");

		VBO = new Douter::VertexBuffer(sizeof(vertices), vertices);

		VAO = new Douter::VertexArray();
		VAO->AddBuffer(VBO);
		VAO->Add<float>(3);
	}

	virtual void OnDettach()
	{
	}

	virtual void Update(double deltaTime)
	{
	}

	virtual void OnImGuiRender()
	{
	}

	virtual void Draw(SDL_Renderer* renderer)
	{
		shader->Bind();
		VAO->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};