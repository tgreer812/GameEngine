#include "Triangle.h"
#include <gdiplus.h>

Triangle::Triangle(Point a, Point b, Point c) {
    points[0] = a;
    points[1] = b;
    points[2] = c;
}

void Triangle::Render(HDC hdc) {
    Graphics graphics(hdc);

    SolidBrush redBrush(Color(255, 255, 0, 0));
    PointF pointsF[3];

    for (int i = 0; i < 3; i++) {
        pointsF[i] = PointF(points[i].X, points[i].Y);
    }


    graphics.FillPolygon(
        &redBrush,
        pointsF,
        3
    );
}

void Triangle::Update(std::chrono::nanoseconds dt)
{
    //float speed = 0.1f; // You can adjust this value to control the movement speed
    //float deltaTimeInSeconds = std::chrono::duration<float>(dt).count();
    OutputDebugStringW(L"Working!\n");
    for (auto& point : points)
    {
        point.X += 1;
    }
}

