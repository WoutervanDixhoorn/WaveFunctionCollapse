#pragma once
#include "Douter/Douter.h"

#include "imgui.h"
#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

#include <iostream>

class WaveLayer : public Douter::ILayer
{
private:
	Douter::Camera* m_Camera;
	glm::vec3 camPos;

	Douter::Texture2D* m_UvTexture;
	Douter::Texture2D* m_CobbleTexture;
	
	Douter::EventHandler* m_EventHandler;

public:

	virtual void OnAttach()
	{
		m_Camera = new Douter::OrthoCamera();
		Douter::Application::Get().SetActiveCamera(m_Camera); //TODO: Make this work better or automatic
		camPos = glm::vec3(0.0f);

		m_UvTexture = new Douter::Texture2D("res\\textures\\uvmap.jpg");
		m_CobbleTexture = new Douter::Texture2D("res\\textures\\cobble.png");

		m_EventHandler = new Douter::EventHandler();
	}

	virtual void OnDettach()
	{
		delete m_Camera;

		delete m_UvTexture;
		delete m_CobbleTexture;
	}

	virtual void OnEvent(Douter::IEvent& e)
	{
		m_EventHandler->handleEvent<Douter::WindowResizeEvent>(e, [](Douter::WindowResizeEvent& e) {
			e.Print();
		});

		m_EventHandler->handleEvent<Douter::WindowMinimizeEvent>(e, [](Douter::WindowMinimizeEvent& e) {
			e.Print();
		});

		m_EventHandler->handleEvent<Douter::KeyPressEvent>(e, [&](Douter::KeyPressEvent& e) {
			e.Print();

			//Temp test code
			if (e.GetKey() == 100)
				camPos.x -= 0.5;
			if (e.GetKey() == 97)
				camPos.x += 0.5;

			if(e.GetKey() == 119)
				camPos.y -= 0.5;
			if (e.GetKey() == 115)
				camPos.y += 0.5;
		});
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