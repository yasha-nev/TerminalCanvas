#include "terminalcanvas.h"

int main()
{
    vector<double> x = linespace(5 * -3.14, 5 * 3.14, 1000);
    vector<double> y(x.size(), 0);

    for (size_t i = 0; i < y.size(); i++){
        y[i] = sin(x[i]);
    }

    TerminalCanvas canvas;

    canvas.InitMap();
    canvas.Plot(x, y);
    canvas.Draw();

    return 0;
}
