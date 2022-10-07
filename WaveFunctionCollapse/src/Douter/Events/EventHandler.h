#pragma once
#include <functional>

#include "WindowEvents.h"
#include "KeyboardEvents.h"

namespace Douter
{
	//Forward declare
	IEvent* fromWindowEvent(SDL_Event& e);
	IEvent* fromKeyEvent(SDL_Event& e);
	IEvent* fromMouseEvent(SDL_Event& e);

	static IEvent& FromSDLEvent(SDL_Event& e)
	{	
		IEvent* dEvent = nullptr;
		if (e.type == SDL_WINDOWEVENT)
			dEvent = fromWindowEvent(e);
		else {
			dEvent = fromKeyEvent(e);
			if(dEvent == nullptr) dEvent = fromMouseEvent(e);
		}

		if (dEvent == nullptr)
			dEvent = new IEvent();

		return *dEvent; //NOTE: Delete event in 'event handler'
	}

	static IEvent* fromWindowEvent(SDL_Event& e)
	{
		EventType type = (EventType)e.window.event;

		switch (type)
		{
		case EventType::WindowCloseEvent: return new WindowCloseEvent(); break;
		case EventType::WindowResizeEvent: return new WindowResizeEvent(e.window.data1, e.window.data2); break;
		case EventType::WindowMinimizeEvent: return new WindowMinimizeEvent(true); break;
		case EventType::WindowUnminimizeEvent: return new WindowMinimizeEvent(false); break;
		}

		return nullptr;
	}

	static IEvent* fromKeyEvent(SDL_Event& e)
	{
		EventType type = (EventType)e.type;

		switch (type)
		{
		case EventType::KeyPressEvent: return new KeyPressEvent(e.key.keysym.sym); break;
		}

		return nullptr;
	}

	static IEvent* fromMouseEvent(SDL_Event& e)
	{
		EventType type = (EventType)e.type;

		switch (type)
		{
		//case EventType::KeyPressEvent: return new WindowCloseEvent(); break;
		}

		return nullptr;
	}

	class EventHandler
	{
	public:
		EventHandler() = default;

		template<typename T>
		bool handleEvent(IEvent& e, std::function<void(T&)> cFunc)
		{
			if (e.m_Handled)
				return true;

			if (dynamic_cast<T*>(&e) != nullptr) {
				cFunc(dynamic_cast<T&>(e));
				e.m_Handled = true; //NOTE: Later support events traveling through layers!
			}
;			return e.m_Handled;
		};

	};
}