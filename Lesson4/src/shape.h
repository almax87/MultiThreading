#pragma once
#include <string>
#include <cmath>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double volume() const { return 0.0; }
    virtual Shape* shift(int m, int n, int k);
};

class Movable : public Shape {
public:
    double volume() const override { return 0.0; }
};

class notMovable : public Shape {
};

// 2D Shapes
class Line : public Movable
{
public:
    Line(std::vector<std::vector<int>> _verticles);
    double area() const { return 0.0; }
    Shape* shift (int m, int n, int k) override;
private: 
    std::vector<std::vector<int>> verticles;
};

class Square : public Movable {
public:
    Square(std::vector<std::vector<int>> _verticles);
    double area() const;
    Shape* shift (int m, int n, int k) override;
private:
    std::vector<std::vector<int>> verticles;
};

class Circle : public notMovable {
public:
    Circle(int centerX, int centerY, double radius);
    double area() const override;
    
private:
    int centerX, centerY;
    double radius;
};

// 3D Shapes
class Cube : public Movable {
public:
    Cube(std::vector<std::vector<int>> _verticles);
    double area() const;
    double volume() const;
    Shape* shift(int m, int n, int k) override;
private:
    std::vector<std::vector<int>> verticles;
};

class Cylinder : public notMovable {
public:
    Cylinder(int centerX, int centerY, double radius, double height);
    double area() const;
    double volume() const;
    
private:
    int centerX, centerY;
    double radius;
    double height;
};