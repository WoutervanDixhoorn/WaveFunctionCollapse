#pragma once
#include "ILayer.h"
#include <SDL.h>

//#include <imgui.h>
//#include <imgui_impl_sdl.h>
//#include <imgui_impl_opengl3.h>

namespace Douter {

	class ImGuiLayer : public ILayer
	{
	public:

		virtual void OnAttach();
		virtual void OnDettach();

		virtual void HandleSDLEvent(SDL_Event& e);

		virtual void Update(double deltaTime);

		virtual void OnImGuiRender();

		static void Begin();
		static void End();
	};

}