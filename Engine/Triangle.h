#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Entity.h"
#include <Windows.h>
#include <gdiplus.h>
#include <gdiplustypes.h>
#include <array>

using namespace Gdiplus;

class Triangle :public Entity
{
    public: 
        Triangle(Point, Point, Point);

        void Render(HDC) override;

        void Update(std::chrono::nanoseconds) override;

    private:
        std::array<Point, 3> points;
};

#endif

