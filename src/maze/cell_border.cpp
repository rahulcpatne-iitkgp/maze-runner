#include "cell_border.h"
#include <cmath>
#include <tuple>
using namespace std;

LineSegment::LineSegment(double x1, double y1, double x2, double y2)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

LineSegment::LineSegment(tuple<double, double, double, double> coords)
{
    tie(x1_, y1_, x2_, y2_) = coords;
}

string LineSegment::PrintStringSVG(const string &color) const
{
    return "<line x1=\"" + to_string(x1_ * 30) + "\" x2=\"" + to_string(x2_ * 30) +
           "\" y1=\"" + to_string(y1_ * 30) + "\" y2=\"" + to_string(y2_ * 30) +
           "\" stroke=\"" + color + "\" stroke-linecap=\"round\" stroke-width=\"3\" />";
}

tuple<double, double, double, double> LineSegment::GetCoordinates() const
{
    return make_tuple(x1_, y1_, x2_, y2_);
}

tuple<double, double, double, double> CellBorder::GetCellCenters() const
{
    // Calculate the midpoint of the line

    double midX = (x1_ + x2_) / 2.0;
    double midY = (y1_ + y2_) / 2.0;

    // Calculate the normal vector to the line (perpendicular)
    double dx = x2_ - x1_;
    double dy = y2_ - y1_;
    double length = sqrt(dx * dx + dy * dy);

    // Normalize and rotate 90 degrees to get perpendicular vector
    // Perpendicular vector is (-dy/length, dx/length)
    double nx = -dy / length;
    double ny = dx / length;

    // The cell centers are 0.5 units away from the midpoint along the normal vector
    double cx1 = midX + 0.5 * nx;
    double cy1 = midY + 0.5 * ny;
    double cx2 = midX - 0.5 * nx;
    double cy2 = midY - 0.5 * ny;
    return make_tuple(cx1, cy1, cx2, cy2);
}