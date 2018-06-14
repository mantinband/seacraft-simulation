#include <iostream>
#include <fstream>
#include "Controller.h"
#include "View.h"

int main(int argc, char **argv) {
    Controller controller;
    ifstream ifs;


    if (argc < 2){
        cerr << "Invalid initialization. [expected: ./executionName portFile]" << endl;
        exit(1);
    }

    ifs.open(argv[1],ios_base::in);

    try {
        controller.run(ifs);
    } catch (exception &e){
        cerr << e.what() << endl;
    }

    return 0;
}