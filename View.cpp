//
// Created by amichai on 11/06/18.
//

#include "View.h"

void View::show() const {
    cout << "Display size: " << displaySize << ", scale: " << scale << ", origin: ";
    origin.print();
    cout << endl;

    for (int i=displaySize-1; i>=0; i--){
        if (i%3 == 0){
            cout << setw(5) << origin.y+i*scale << " ";
        } else {
            cout << setw(6) << "";
        }
        for (int j=0; j<displaySize; j++){
            Point p(origin.x+scale*j,origin.y+scale*i);

            string objectInitial = Model::getInstance().getObjectInitialsAt(p,scale);

            if (objectInitial.empty()){
                cout << ". ";
            } else {
                cout << objectInitial;
            }
        }
        cout << endl;
    }

    for (int i=0; i<ceil(displaySize/3.0); i++){
        if (i == 0){
            cout << setw(7) << origin.x+scale*(i*3);
        } else {
            cout << setw(6) << origin.x + scale * (i*3);
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
