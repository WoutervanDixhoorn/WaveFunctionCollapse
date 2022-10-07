#pragma once
#include "Events/Event.h"

#include <SDL.h>

namespace Douter {

	class ILayer
	{
	public:
		
		virtual void OnAttach() {};
		virtual void OnDettach() {};

		virtual void Update(double deltaTime) = 0;
		virtual void OnEvent(IEvent& e) {};
		virtual void Draw(SDL_Renderer* renderer) {};
		virtual void OnImGuiRender() {};

	};

}