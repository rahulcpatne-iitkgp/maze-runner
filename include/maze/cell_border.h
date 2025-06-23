#ifndef CELLBORDER_H
#define CELLBORDER_H

#include <string>
using namespace std;

class LineSegment {
public:
    LineSegment(double, double, double, double);
    LineSegment(tuple<double, double, double, double>);
    tuple<double, double, double, double> GetCoordinates() const;
    string PrintStringSVG(const string&) const;

protected:
    double x1_, y1_, x2_, y2_;
};

class CellBorder : public LineSegment {
public:
    using LineSegment::LineSegment;
    tuple<double, double, double, double> GetCellCenters() const;
};

#endif