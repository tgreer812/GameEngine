#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <chrono>

class Entity
{
	public:
		virtual void Render(HDC) = 0;
		virtual void Update(std::chrono::nanoseconds) = 0;
};

