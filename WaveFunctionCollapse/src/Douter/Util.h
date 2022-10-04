#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

namespace Douter
{
	//Chrono timer;
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

	class Timer
	{
	private:
		TimePoint m_StartTime;
		TimePoint m_EndTime;
		bool m_Running = false;

	public:
		void Start()
		{
			m_StartTime = std::chrono::high_resolution_clock::now();
			m_Running = true;
		}

		void Stop()
		{
			m_EndTime = std::chrono::high_resolution_clock::now();
			m_Running = false;
		}

		double elapsedMilliseconds()
		{
			TimePoint endTime;

			if (m_Running)
			{
				endTime = std::chrono::high_resolution_clock::now();
			}
			else
			{
				endTime = m_EndTime;
			}

			double dur = std::chrono::duration<double, std::milli>(endTime - m_StartTime).count();
			return dur;
		}

		double elapsedSeconds()
		{
			return elapsedMilliseconds() / 1000.0;
		}

	};

}