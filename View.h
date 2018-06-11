//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_VIEW_H
#define SEACRAFT_SIMULATION_VIEW_H


#include "Geometry.h"
#include <cmath>
#include "Model.h"
class View {
public:
    static const int MIN_DISPLAY_SIZE = 6;
    static const int MAX_DISPLAY_SIZE = 30;
    static const int DEFAULT_DISPLAY_SIZE = 25;
    static const int DEFAULT_SCALE = 2;
    static const int DEFAULT_ORIGIN_X = -10;
    static const int DEFAULT_ORIGIN_Y = -10;

    View();

    void show() const;

    void setDisplaySize(int displaySize);

    void setScale(double scale);

    void setOrigin(const Point &origin);

    void restoreDefault();

    struct invalidMapSize : exception{
        string s = "ERROR: Invalid size. [expected: integer between "
                + to_string(MIN_DISPLAY_SIZE) + " and "
                + to_string(MAX_DISPLAY_SIZE) + "]";
        const char * what() const throw() override {
            return s.c_str();
        }
    };
private:
    int displaySize;
    double scale;
    Point origin;
};

#endif //SEACRAFT_SIMULATION_VIEW_H
