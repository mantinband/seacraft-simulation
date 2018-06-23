//
// Created by amichai on 11/06/18.
//

#ifndef SEACRAFT_SIMULATION_VIEW_H
#define SEACRAFT_SIMULATION_VIEW_H


#include "Geometry.h"
#include <cmath>
#include "Model.h"

/************************************************/
/*  Class prints sea to standard output stream. */
/*  it is printed as a two dimensional matrix.  */
/*  it supports actions such as changing scale  */
/*  origin and size.                            */
/************************************************/
class View {
public:
    static const int MIN_DISPLAY_SIZE = 6;
    static const int MAX_DISPLAY_SIZE = 30;
    static const int DEFAULT_DISPLAY_SIZE = 25;
    static const int DEFAULT_SCALE = 2;
    static const int DEFAULT_ORIGIN_X = -10;
    static const int DEFAULT_ORIGIN_Y = -10;

    View();
    View(const View& rhs);
    View& operator=(const View& rhs);
    View(View&& rhs) noexcept;
    View& operator=(View&& rhs) noexcept;
    virtual ~View() = default;

    void show() const;

    /*  sets the map's size to given value  */
    void setDisplaySize(int displaySize);

    /*  sets the map's scale to given value */
    void setScale(double scale);

    /*  set's map's lower left corner to given point    */
    void setOrigin(const Point &origin);

    /*  restores map's defualt values as defined above  */
    void restoreDefault();


    int getDisplaySize() const;

    double getScale() const;

    const Point &getOrigin() const;

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
