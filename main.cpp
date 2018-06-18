#include <iostream>
#include <fstream>
#include "Controller.h"

int main(int argc, char **argv) {
    Controller controller;
    ifstream ifs;

    /*  expected 2 arguments:
     *  1) execution name
     *  2) port data file  */
    if (argc < 2){
        cerr << "Invalid initialization. [expected: ./executionName portFile]" << endl;
        exit(1);
    }

    ifs.open(argv[1],ios_base::in);

    try {
        /*  start controller    */
        controller.run(ifs);
    } catch (exception &e){
        cerr << e.what() << endl;
        exit(2);
    }

    return 0;
}