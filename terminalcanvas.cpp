#include "terminalcanvas.h"
#include <stdio.h>

TerminalCanvas::TerminalCanvas(){
    canvas     = vector<vector<int>>(40, vector<int> (100, 0));
    black      = "\33[1;40m";
    white      = "\33[1;47m";
    red        = "\33[1;41m";
    green      = "\33[1;42m";
    yellow     = "\33[1;43m";
    blue       = "\33[1;44m";
    colorReset = "\33[0m";
    accuracity = 0.1;
}

string TerminalCanvas::getColor(int color){
    if (color == 0){
        return black;
    }
    else if(color == 1){
        return white;
    }
    else if (color == 2){
        return red;
    }
    else if(color == 3){
        return green;
    }
    else if (color == 4){
        return yellow;
    }
    else if(color == 5){
        return blue;
    }
    else{
        return black;
    }
}

void TerminalCanvas::InitMap(){
    for (size_t i = 0; i < canvas.size(); i++){
        for (size_t j = 0; j < canvas[i].size(); j++){
            canvas[i][j] = 1;
        }
    }
}

void TerminalCanvas::Plot(vector<double> &x, vector<double> &y){
    double max_x = x[0];
    double min_x = x[0];
    double max_y = y[0];
    double min_y = y[0];

    for (size_t i = 0; i < x.size(); i++){
        if (max_x < x[i]) max_x = x[i];
        if (min_x > x[i]) min_x = x[i];
    }

    for (size_t i = 0; i < y.size(); i++){
        if (max_y < y[i]) max_y = y[i];
        if (min_y > y[i]) min_y = y[i];
    }

    vector<double> ox(canvas[0].size());
    vector<double> oy(canvas.size());

    double step = (max_x - min_x) / ox.size();
    for (size_t i = 0; i < ox.size(); i++){
        ox[i] = min_x + step * i;
    }

    step = (max_y - min_y) / oy.size();
    for (size_t i = 0; i < oy.size(); i++){
        oy[i] = min_y + step * i;
    }

    for (size_t i = 0; i < oy.size(); i++){
        vector<size_t> fit_y;
        for (size_t j = 0; j < y.size(); j++){
            if (abs(oy[i] - y[j]) < accuracity){
                fit_y.push_back(j);
            }
        }
        if (fit_y.empty()){
            for (size_t j = 0; j < x.size(); j++){
                canvas[i][j] = 1;
            }
        }
        else{
            vector<size_t> fit_x;
            for (size_t j = 0; j < ox.size(); j++){
                for (size_t s = 0; s < fit_y.size(); s++){
                    if (abs(ox[j] - x[fit_y[s]]) < accuracity){
                        fit_x.push_back(j);
                    }
                }
            }
            for (size_t j = 0; j < ox.size(); j++){
                bool flag = 0;
                for (size_t s = 0; s < fit_x.size(); s++){
                    if (fit_x[s] == j){
                        flag = 1;
                        break;
                    }
                }
                if (flag){
                    canvas[i][j] = 2;
                }
                else{
                    canvas[i][j] = 1;
                }
            }
        }
    }
}

void TerminalCanvas::Draw(){
    for (size_t i = 0; i < canvas.size(); i++){
        for (size_t j = 0; j < canvas[i].size(); j++){
            string color = getColor(canvas[i][j]);
            printf("%s %s", color.c_str(), colorReset.c_str());
        }
        printf("\n");
    }
}

vector<double> linespace(double start, double end, size_t count){
    double step = (end - start) / count;
    vector<double> arr(count);
    for (size_t i = 0; i < arr.size(); i++){
        arr[i] = start + step * i;
    }
    return arr;
}
