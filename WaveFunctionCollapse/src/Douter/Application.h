#pragma once
#include <vector>
#include <SDL.h>
#undef main

#include "Rendering/Camera.h"
#include "ILayer.h"
#include "ImGuiLayer.h"
#include "Events/EventHandler.h"

namespace Douter {

	class Application
	{
	private:
		static Application* s_Instance;

		EventHandler* m_EventHandler;

		bool m_Running = false;
		int m_ScreenWidth, m_ScreenHeight;

		std::vector<Douter::ILayer*> m_Layers;
		ImGuiLayer* m_ImGuiLayer;

		Camera* m_ActiveCamera;

	public:
		Application(int width = 1280, int height = 720);
		~Application();

		inline static Application& Get() { return *s_Instance; };
		inline SDL_Window* GetWindow() { return m_Window; };
		inline SDL_GLContext GetContext() { return m_GraphicsContext; }

		void SetActiveCamera(Camera* camera) { m_ActiveCamera = camera; };
		inline Camera& GetActiveCamera() { return *m_ActiveCamera; }

		void Run();

		void HandleEvents(IEvent& e);

		void AttachLayer(ILayer* layer)
		{
			m_Layers.push_back(layer);
			layer->OnAttach();
		}

		void DettachLayer(ILayer* layer)
		{
			remove(m_Layers.begin(), m_Layers.end(), layer);
			layer->OnDettach();
		}

		virtual void Init() = 0;

		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };		

	private:
		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
		SDL_GLContext m_GraphicsContext;
	};

}