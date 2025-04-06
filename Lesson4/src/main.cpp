#include "shape.h"

int main()
{
    Shape* line = new Line({{2,3}, {2,2}});
    Shape* square = new Square({{1,1}, {2,2}, {3,3}, {4,4}});
    Shape* cube = new Cube({{1,2,3}, {3,4,5}, {4,5,6}, {7,8,9}});

    line->shift(1,1,0);
    cube->shift(2,3,5);

    return 0;
}