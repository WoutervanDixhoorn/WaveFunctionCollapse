#pragma once
#include "Douter/ILayer.h"
#include "Douter/Rendering/Buffer.h"
#include "Douter/Rendering/Shader.h"
#include "Douter/Rendering/Renderer.h"
#include "Douter/Rendering/Texture2D.h"
#include "Douter/Rendering/OrthoCamera.h"

#include "imgui.h"
#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

class WaveLayer : public Douter::ILayer
{
private:
	Douter::Camera* m_Camera;
	glm::vec3 camPos;

	Douter::Texture2D* m_UvTexture;
	Douter::Texture2D* m_CobbleTexture;
	
public:

	virtual void OnAttach()
	{
		m_Camera = new Douter::OrthoCamera();
		Douter::Application::Get().SetActiveCamera(m_Camera); //TODO: Make this work better or automatic
		camPos = glm::vec3(0.0f);

		m_UvTexture = new Douter::Texture2D("res\\textures\\uvmap.jpg");
		m_CobbleTexture = new Douter::Texture2D("res\\textures\\cobble.png");
	}

	virtual void OnDettach()
	{
		delete m_Camera;

		delete m_UvTexture;
		delete m_CobbleTexture;
	}

	virtual void Update(double deltaTime)
	{
		m_Camera->SetPosition(camPos.x, camPos.y, camPos.z);
	}


	virtual void OnImGuiRender()
	{
		ImGui::Begin("Camera Controller");

		ImGui::SliderFloat3("Translation", glm::value_ptr(camPos), -5.0f, 5.0f);
		
		ImGui::End();
	}

	virtual void Draw(SDL_Renderer* renderer)
	{
		Douter::Renderer2D::DrawRect(5, 5, 2, 2, *m_UvTexture, 0.5f);
		Douter::Renderer2D::DrawRect(-5, 5, 2, 2, { 1.0f, 0.5f, 0.7f });
		Douter::Renderer2D::DrawRect(5, -5, 2, 2, { 1.0f, 0.5f, 0.7f });
		Douter::Renderer2D::DrawRect(-5, -5, 2, 2, *m_CobbleTexture, 2.5f);
	}
};