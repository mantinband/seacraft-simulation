//
// Created by amichai on 11/06/18.
//

#include "View.h"

void View::show() const {
    cout << "Display size: " << displaySize << ", scale: " << scale << ", origin: ";
    origin.print();
    cout << endl;

    for (int i=displaySize-1; i>=0; i--){
        /*  if current line contains number representing scale indicator  */
        if (i%3 == 0){
            /*  when setting precision it is checked whether the number
             * representing scale is a natural or real number    */
            cout << setw(5) << fixed << setprecision(floor(origin.y+i*scale) == origin.y+i*scale ? 0 : 1) << origin.y+i*scale << " ";
        } else {
            cout << setw(6) << "";
        }
        for (int j=0; j<displaySize; j++){
            Point p(origin.x+scale*j,origin.y+scale*i);

            /*  object initial receives first object found in area if found. empty string otherwise */
            string objectInitial = Model::getInstance().getObjectInitialsAt(p,scale);

            if (objectInitial.empty()){
                cout << ". ";
            } else {
                cout << objectInitial;
            }
        }
        cout << endl;
    }

    /*  print bottom numbers representing scale */
    for (int i=0; i<ceil(displaySize/3.0); i++){
        if (i == 0){
            cout << setw(7) << fixed << setprecision(floor(origin.y+i*scale) == origin.y+i*scale ? 0 : 1) << origin.x+scale*(i*3);
        } else {
            cout << setw(6) << fixed << setprecision(floor(origin.y+i*scale) == origin.y+i*scale ? 0 : 1) << origin.x + scale * (i*3);
        }
    }
    cout << endl;
}

View::View()
: displaySize(DEFAULT_DISPLAY_SIZE), scale(DEFAULT_SCALE),origin(DEFAULT_ORIGIN_X,DEFAULT_ORIGIN_Y) {}

void View::setDisplaySize(int displaySize) {
    if (displaySize < MIN_DISPLAY_SIZE || displaySize > MAX_DISPLAY_SIZE){
        throw invalidMapSize();
    }
    View::displaySize = displaySize;
}

void View::setScale(double scale) {
    View::scale = scale;
}

void View::setOrigin(const Point &origin) {
    View::origin = origin;
}

void View::restoreDefault() {
    displaySize = DEFAULT_DISPLAY_SIZE;
    scale = DEFAULT_SCALE;
    origin = Point(DEFAULT_ORIGIN_X,DEFAULT_ORIGIN_Y);
}

View::View(const View &rhs) {
    displaySize = rhs.getDisplaySize();
    scale = rhs.getScale();
    origin = rhs.getOrigin();
}

int View::getDisplaySize() const {
    return displaySize;
}

double View::getScale() const {
    return scale;
}

const Point &View::getOrigin() const {
    return origin;
}

View &View::operator=(const View& rhs) {
    displaySize = rhs.getDisplaySize();
    scale = rhs.getScale();
    origin = rhs.getOrigin();

    return *this;
}

View::View(View &&rhs) noexcept {
    displaySize = rhs.getDisplaySize();
    scale = rhs.getScale();
    origin = rhs.getOrigin();
    rhs.restoreDefault();
}

View &View::operator=(View &&rhs) noexcept {
    displaySize = rhs.getDisplaySize();
    scale = rhs.getScale();
    origin = rhs.getOrigin();
    rhs.restoreDefault();
    return *this;
}
