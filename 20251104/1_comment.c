#include <stdio.h>
#include <math.h>

// 定义圆周率常量，通过反余弦函数计算获得精确值
const double pi = acos(-1);

/***
计算圆的面积
r 圆的半径
return 计算得到的圆的面积
***/
double CircleArea(double r);

/***
计算矩形的面积
l 矩形的长度
w 矩形的宽度
return 计算得到的矩形的面积
***/
double RectangleArea(double l, double w);

/***
打印圆和矩形的面积
circle 圆的面积
rect 矩形的面积
return 无返回值
***/
void PrintAreas(double circle, double rect);

int main(void)
{
    // 初始化变量：圆的半径为5.0，矩形的长为4.0、宽为3.0
    double radius=5.0, length=4.0, width=3.0;
    // 声明变量用于存储计算得到的面积
    double circle, rect;

    // 调用CircleArea函数计算圆的面积
    // 参数传递过程：将radius作为实参传递给形参r，函数内部使用r计算面积后返回结果赋值给circle
    circle = CircleArea(radius);

    // 调用RectangleArea函数计算矩形的面积
    // 参数传递过程：将length和width作为实参分别传递给形参l和w，函数内部使用l和w计算面积后返回结果赋值给rect
    rect = RectangleArea(length, width);

    // 调用PrintAreas函数打印面积结果
    // 参数传递过程：将circle和rect作为实参分别传递给形参circle和rect，函数内部使用这两个参数进行格式化输出
    PrintAreas(circle, rect);

    return 0;
}

/***
计算圆的面积
r 圆的半径
计算得到的圆的面积，计算公式：π * r * r
***/
double CircleArea(double r)
{
    double result;       // 声明变量存储计算结果
    result = pi * r * r; // 使用圆面积公式计算
    return result;       // 返回计算得到的面积
}

/***
计算矩形的面积
l 矩形的长度
w 矩形的宽度
return 计算得到的矩形的面积，计算公式：l * w
 */
double RectangleArea(double l, double w)
{
    double result;       // 声明变量存储计算结果
    result = l * w;      // 使用矩形面积公式计算
    return result;       // 返回计算得到的面积
}

/***
打印圆和矩形的面积
circle 圆的面积，以10位小数精度输出
rect 矩形的面积，以2位小数精度输出
return 无返回值
***/
void PrintAreas(double circle, double rect)
{
    // 格式化输出两个面积值，圆面积保留10位小数，矩形面积保留2位小数
    printf("Circle Area: %.10f, Rectangle Area: %.2f\n", circle, rect);
}
