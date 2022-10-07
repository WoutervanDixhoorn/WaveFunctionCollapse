#pragma once
#include "Event.h"

namespace Douter
{

	class WindowCloseEvent : public IEvent
	{
	private:

	public:
		WindowCloseEvent()
		{
		}

		EVENT_TYPE_FUNCTIONS(EventType::WindowCloseEvent)
	};

	class WindowResizeEvent : public IEvent
	{
	private:
		int m_Width, m_Height;

	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height)
		{
		}

		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }

		virtual inline void Print()
		{
			std::cout << toString() << "| Width: " << GetWidth() << " | Height:" << GetHeight() << "\n";
		}

		EVENT_TYPE_FUNCTIONS(EventType::WindowResizeEvent)
	};

	class WindowMinimizeEvent : public IEvent
	{
	private:
		bool m_Minimized;

	public:
		WindowMinimizeEvent(bool minimized)
			: m_Minimized(minimized)
		{
		}

		inline int GetMinimized() { return m_Minimized; }

		virtual inline void Print()
		{
			std::cout << toString() << "| Minimized: " << (GetMinimized() ? "True" : "False") << "\n";
		}

		EVENT_TYPE_FUNCTIONS(EventType::WindowMinimizeEvent)
	};

}