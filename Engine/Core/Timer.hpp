#pragma once
#include <windows.h>

class Timer {
public:
	Timer() {
		QueryPerformanceFrequency(&m_Frequency);
		QueryPerformanceCounter(&m_Start);
		m_Last = m_Start;
	}

	float GetDeltaTime() noexcept {
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);

		float delta = static_cast<float>(
			(current.QuadPart - m_Last.QuadPart) /
			static_cast<double>(m_Frequency.QuadPart)
		);

		m_Last = current;
		
		return delta;
	}

	float GetElapsedTime() const noexcept {
		LARGE_INTEGER current{};
		QueryPerformanceCounter(&current);

		return static_cast<float>(
			(current.QuadPart - m_Start.QuadPart) /
			static_cast<double>(m_Frequency.QuadPart)
		);
	}

private:
	LARGE_INTEGER m_Frequency{};
	LARGE_INTEGER m_Start{};
	LARGE_INTEGER m_Last{};
};