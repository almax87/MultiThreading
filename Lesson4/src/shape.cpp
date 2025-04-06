#include "shape.h"

// Line implementation
Line::Line(std::vector<std::vector<int>> _verticles) : verticles(std::move(_verticles)) {}

Shape* Line::shift(int m, int n, int k)
{
    verticles[0][0] += m;
    verticles[0][1] += n;
    return this;
}

// Square implementation
Square::Square(std::vector<std::vector<int>> _verticles) : verticles(std::move(_verticles)) {}

double Square::area() const {
    int a = abs(verticles[0][0] - verticles[1][0]);
    int b = abs(verticles[0][1] - verticles[1][1]);
    return a * b;
}

Shape* Square::shift (int m, int n, int k)
{
    for (auto& i : verticles)
    {
        i[0] += m;
        i[1] += n;
    }
    return this;
}

// Circle implementation
Circle::Circle(int centerX, int centerY, double radius)
    : centerX(centerX), centerY(centerY), radius(radius) {}

double Circle::area() const {
    return M_PI * radius * radius;
}

// Cube implementation
Cube::Cube(std::vector<std::vector<int>> _verticles) : verticles(std::move(_verticles)) {}

double Cube::area() const {
    int a = abs(verticles[0][0] - verticles[1][0]);
    int b = abs(verticles[0][1] - verticles[1][1]);
    int c = abs(verticles[0][2] - verticles[1][2]);
    return 2 * (a*b + a*c + b*c);
}

double Cube::volume() const {
    int a = abs(verticles[0][0] - verticles[1][0]);
    int b = abs(verticles[0][1] - verticles[1][1]);
    int c = abs(verticles[0][2] - verticles[1][2]);
    return a * b * c;
}

Shape* Cube::shift(int m, int n, int k)
{
    for (auto& i : verticles)
    {
      i[0] += m;
      i[1] += n;
      i[2] += k;
    }
    return this;
}

// Cylinder implementation
Cylinder::Cylinder(int centerX, int centerY, double radius, double height)
    : centerX(centerX), centerY(centerY), radius(radius), height(height) {}

double Cylinder::area() const {
    return 2 * M_PI * radius * (radius + height);
}

double Cylinder::volume() const {
    return M_PI * radius * radius * height;
}



