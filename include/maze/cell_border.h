#ifndef CELLBORDER_H
#define CELLBORDER_H

#include <string>
using namespace std;

class CellBorder {
public:
    CellBorder(double, double, double, double);
    CellBorder(tuple<double, double, double, double>);

    string PringStringSVG(const string&) const;
    void GetCellCenters(double&, double&, double&, double&) const;
    tuple<double, double, double, double> GetCoordinates() const;

protected:
    double x1_, y1_, x2_, y2;
};
#endif