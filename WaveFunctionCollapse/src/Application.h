#pragma once
#include <vector>
#include <SDL.h>
#undef main

#include "ILayer.h"
#include "ImGuiLayer.h"

namespace Douter {

	class Application
	{
	public:
		Application(int width = 1280, int height = 720);
		~Application();

		inline static Application& Get() { return *s_Instance; };
		inline SDL_Window* GetWindow() { return m_Window; };
		inline SDL_GLContext GetContext() { return m_GraphicsContext; }

		void Run();

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

		float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	private:
		static Application* s_Instance;

		bool m_Running = false;
		int m_ScreenWidth, m_ScreenHeight;

		std::vector<Douter::ILayer*> m_Layers;
		ImGuiLayer* m_ImGuiLayer;

		

	private:
		SDL_Window* m_Window = NULL;
		SDL_GLContext m_GraphicsContext;
	};

}