#include "GameEngine.h"
#include "Entity.h" // Assuming you have an Entity class
#include "Triangle.h"
#include <thread>
#include <chrono>
#include <vector>

GameEngine::GameEngine(HWND hWnd)
    : hWnd(hWnd),
    fps(60),
    tickrate(60),
    entities({}) {
    Triangle* myTriangle = new Triangle(
        Point(100, 100),
        Point(50, 300),
        Point(150, 300)
    );
    this->entities.push_back(myTriangle);
}


void GameEngine::Start()
{
    std::thread gameLoopThread(&GameEngine::GameLoop, this);
    gameLoopThread.detach();
}

void GameEngine::Update(std::chrono::nanoseconds dt)
{
    for (auto& entity : entities)
    {
        entity->Update(dt);
    }
}

void GameEngine::Render(HDC hdc)
{
    // Clear the background
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(255, 255, 255)); // Change the color as needed
    FillRect(hdc, &clientRect, backgroundBrush);
    DeleteObject(backgroundBrush);

    // Render entities
    for (auto& entity : entities)
    {
        entity->Render(hdc);
    }
}


void GameEngine::GameLoop()
{
    using namespace std::chrono;

    auto timePerFrame = duration_cast<nanoseconds>(seconds(1)) / fps;
    auto timePerTick = duration_cast<nanoseconds>(seconds(1)) / tickrate;

    high_resolution_clock::time_point currentTime, previousTime;
    currentTime = previousTime = high_resolution_clock::now();
    nanoseconds lag(0);

    while (true)
    {
        currentTime = high_resolution_clock::now();
        auto elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        lag += duration_cast<nanoseconds>(elapsedTime);

        while (lag >= timePerTick)
        {
            // Update game state (e.g. entities' positions, physics, AI, etc.)
            Update(timePerTick);

            lag -= timePerTick;
        }

        // Render
        HDC hdc = GetDC(hWnd);
        if (hdc)
        {
            Render(hdc);
            ReleaseDC(hWnd, hdc);
        }

        // Sleep
        auto sleepTime = timePerFrame - (high_resolution_clock::now() - currentTime);
        if (sleepTime > nanoseconds::zero())
        {
            std::this_thread::sleep_for(sleepTime);
        }
    }
}
