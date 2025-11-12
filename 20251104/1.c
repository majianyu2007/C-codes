#include <stdio.h>
#include <math.h>

const double pi = acos(-1);

double CircleArea(double r);
double RectangleArea(double l, double w);
void PrintAreas(double circle, double rect);

int main(void)
{
    double radius=5.0, length=4.0, width=3.0;
    double circle, rect;

    circle = CircleArea(radius);
    rect = RectangleArea(length, width);
    PrintAreas(circle, rect);

    return 0;
}

double CircleArea(double r)
{
    double result;
    result = pi * r * r;
    return result;
}

double RectangleArea(double l, double w)
{
    double result;
    result = l * w;
    return result;
}

void PrintAreas(double circle, double rect)
{
    printf("Circle Area: %.10f, Rectangle Area: %.2f\n", circle, rect);
}
