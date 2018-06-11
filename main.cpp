#include <iostream>
#include "Controller.h"
#include "View.h"

int main() {
    View view;
    Controller controller(&view);

    controller.initiate();


    return 0;
}