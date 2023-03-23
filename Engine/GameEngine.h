#pragma once
#include <Windows.h>
#include <vector>
#include "Entity.h"
#include <chrono>
class GameEngine
{
	public:
		GameEngine(HWND);

		// Start the game loop
		void Start();

		// Loop through entities and render them
		void Render(HDC);
		void Update(std::chrono::nanoseconds);

	private:
		DWORD fps;
		DWORD tickrate;
		std::vector<Entity*> entities;
		HWND hWnd;

		// Central game loop for telling 
		void GameLoop();
};

