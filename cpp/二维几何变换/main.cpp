#include <iostream>
#include <cmath>
using namespace std;

struct Point
{
    double x;
    double y;
    Point(double mX=0.0, double mY=0.0) : x(mX), y(mY) {}

    void translate(double tx, double ty)
    {
        x += tx;
        y += ty;
    }
    void rotate(double theta, double x0 = 0.0, double y0 = 0.0)
    {
        double dx = x - x0;
        double dy = y - y0;
        x = x0 + dx * cos(theta) - dy * sin(theta);
        y = y0 + dx * sin(theta) + dy * cos(theta);
    }
    void scale(double sx, double sy, double x0 = 0.0, double y0 = 0.0)
    {
        double dx = x - x0;
        double dy = y - y0;
        x = x0 + dx * sx;
        y = y0 + dx * sy;
    }
    // Ax+By+C=0
    Point symmetricPoint(double A, double B, double C) const
    {
        double tmp = (A * x + B * y + C) / (A * A + B * B);
        double x0 = x - 2 * A * tmp;
        double y0 = y - 2 * B * tmp;
        return Point(x0, y0);
    }
};

int main()
{

    cout << "Over!\n";
    return 0;
}