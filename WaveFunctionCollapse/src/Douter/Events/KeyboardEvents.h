#pragma once
#include "Event.h"

namespace Douter
{

	class KeyPressEvent : public IEvent
	{
	private:
		int m_Key;

	public:
		KeyPressEvent(int key)
			: m_Key(key)
		{
		}

		inline int GetKey() { return m_Key; }

		virtual inline void Print()
		{
			std::cout << toString() << "| keyCode: " << m_Key << "\n";
		}

		EVENT_TYPE_FUNCTIONS(EventType::KeyPressEvent)
	};

}