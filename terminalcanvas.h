#ifndef TERMINALCANVAS_H
#define TERMINALCANVAS_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class TerminalCanvas{
public:
    TerminalCanvas();
    void InitMap();
    void Plot(vector<double> &x, vector<double> &y);
    void Draw();

private:
    string getColor(int color);

    vector <vector<int>> canvas;
    string black;
    string white;
    string red;
    string green;
    string yellow;
    string blue;
    string colorReset;
    double accuracity;
};

vector<double> linespace(double start, double end, size_t count);

#endif // TERMINALCANVAS_H
