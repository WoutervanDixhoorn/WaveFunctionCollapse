#pragma once
#include "Douter/ILayer.h"
#include "Douter/Rendering/Buffer.h"
#include "Douter/Rendering/Shader.h"
#include "Douter/Rendering/Renderer.h"
#include "Douter/Rendering/Texture2D.h"

#include "imgui.h"
#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

class WaveLayer : public Douter::ILayer
{
private:
	Douter::Texture2D* m_UvTexture;
	Douter::Texture2D* m_CobbleTexture;

public:

	virtual void OnAttach()
	{
		m_UvTexture = new Douter::Texture2D("res\\textures\\uvmap.jpg");
		m_CobbleTexture = new Douter::Texture2D("res\\textures\\cobble.png");
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
		
		//Douter::Renderer2D::DrawRect(5, 5, *m_UvTexture);
		Douter::Renderer2D::DrawRect(-5, 5, { 1.0f, 0.5f, 0.7f });
		Douter::Renderer2D::DrawRect(5, -5, { 1.0f, 0.5f, 0.7f });
		//Douter::Renderer2D::DrawRect(-5, -5, *m_CobbleTexture);

	}
};