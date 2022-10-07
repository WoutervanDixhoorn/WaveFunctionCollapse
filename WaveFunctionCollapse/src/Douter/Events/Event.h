#pragma once
#include <SDL.h>

#include <string>
#include <iostream>

#define EVENT_TYPE_FUNCTIONS(x) inline EventType GetType() override { return x; }  \
								inline const char* toString() override { return #x; } 

namespace Douter
{
	//List with supported events for sdl 
	//NOTE: Eventually only initialize this list when sdl is used
	enum class EventType
	{
		WindowCloseEvent = SDL_WINDOWEVENT_CLOSE,
		WindowMinimizeEvent = SDL_WINDOWEVENT_MINIMIZED,
		WindowUnminimizeEvent = 12, //NOTE: Cant find correct define
		WindowResizeEvent = SDL_WINDOWEVENT_RESIZED,

		KeyPressEvent = SDL_KEYDOWN,
		KeyReleaseEvent = SDL_KEYUP,

		MousePressEvent = SDL_MOUSEBUTTONDOWN,
		MouseReleaseEvent = SDL_MOUSEBUTTONUP,
		MouseScrollEvent = SDL_MOUSEWHEEL,
		MouseMoveEvent = SDL_MOUSEMOTION,

		Unknown = -1
	};


	class IEvent
	{
		friend class EventHandler;

	protected:
		bool m_Handled;

	public:
		IEvent() 
		: m_Handled(false)
		{
		};
		
		virtual inline void Print() { std::cout << ""; }

		virtual inline EventType GetType() { return EventType::Unknown; }		
		virtual inline const char* toString() { return ""; }
	};

}