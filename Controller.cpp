//
// Created by amichai on 11/06/18.
//

#include "Controller.h"

void Controller::run(ifstream &inputFile) {
    string input;

    try {
        createPorts(inputFile);
    } catch (exception &e){
        throw e;
    }




    cout << "Time " << Model::getInstance().getTime() << ": ";
    cout << "Enter command: ";

    while (getQuery(input) != quit){
        try {
            if (cin.fail()){
                throw invalidInputException();
            }
            
            switch (getQuery(input)) {
                case defaultMap:
                    view->restoreDefault();
                    break;
                case changeMapSize:
                    int size;
                    if (!(cin >> size)){
                        throw invalidMapSize();
                    }

                    view->setDisplaySize(size);

                    break;
                case zoomMap:{
                    double scale;

                    if (!(cin >> scale)){
                        throw invalidScaleException();
                    }

                    view->setScale(scale);
                } break;
                case panMap: {
                    Point p;
                    if (!(cin >> p.x) || !(cin >> p.y)){
                        throw invalidLocationException();
                    }
                    view->setOrigin(p);
                }break;
                case showMap:
                    view->show();
                    break;
                case showStatus:
                    cout << Model::getInstance().getStatus();
                    break;
                case incrementTime:
                    break;
                case createSeacraft:
                    addSeacraft();
                    break;

                default: {
                    string seacraftName;
                    seacraftName = input;
                    if (!(cin >> input)){
                        throw invalidInputException();
                    }

                    switch (getQuery(input)){
                        case course:{
                            double degree;
                            double speed;

                            if (!(cin >> degree) || !(cin >> speed)){
                                throw invalidInputException();
                            }
                            Model::getInstance().setCourse(seacraftName, degree, speed);
                        } break;
                        case position:{
                            Point p;
                            double speed;

                            parseLocation(p,cin);
                            if (!(cin >> speed)){
                                throw invalidInputException();
                            }
                            Model::getInstance().setPosition(seacraftName, p, speed);
                        } break;
                        case destination: {
                            string portName;
                            double speed;

                            if (!(cin >> portName) || !(cin >> speed)){
                                throw invalidInputException();
                            }

                            Model::getInstance().setDestination(seacraftName, portName, speed);
                        } break;
                        case load_at:
                            break;
                        case unload_at:
                            break;
                        case dock_at:
                            break;
                        case attackSeacraft:
                            break;
                        case refuelSeacraft:
                            break;
                        case stopSeacraft:
                            break;
                        default:
                            cerr << "ERROR: Invalid query. try again:" << endl;
                            cin.ignore(INT32_MAX,'\n');
                            break;

                    }
                }
            }
        } catch (exception &e){
            cerr << e.what() << endl;
            cin.ignore(INT32_MAX,'\n');
        }
        cout << "Time " << Model::getInstance().getTime() << ": ";
        cout << "Enter command: ";

        cin >> input;
    }

}


queries Controller::getQuery(string s) {
    if (s == "default") return defaultMap;
    if (s == "size") return changeMapSize;
    if (s == "zoom") return zoomMap;
    if (s == "pan") return panMap;
    if (s == "show") return showMap;

    if (s == "status") return showStatus;
    if (s == "go") return incrementTime;
    if (s == "create") return createSeacraft;

    if (s == "course") return course;
    if (s == "position") return position;
    if (s == "destination") return destination;
    if (s == "load_at") return load_at;
    if (s == "unload_at") return unload_at;
    if (s == "dock_at") return dock_at;
    if (s == "attackSeacraft") return attackSeacraft;
    if (s == "refuelSeacraft") return refuelSeacraft;
    if (s == "stopSeacraft") return stopSeacraft;

    if (s == "exit") return quit;

    return invalidQuery;
}

void Controller::parseLocation(Point &p, istream &is) {
    char c;
    if (!(is >> c) || !(is >> p.x)){ // "(double"
        throw invalidLocationException();
    }
    if (is.fail() || c != '('){
        throw invalidLocationException();
    }
    if (!(is >> c) || !(is >> p.y)){ // ",double
        throw invalidLocationException();
    }
    if (is.fail() || c != ','){
        throw invalidLocationException();
    }

    is >> c;    //  ")"
    if (c != ')'){
        throw invalidLocationException();
    }
}



void Controller::addSeacraft() {
    string craftName;
    string craftType;
    Point point;
    int strength;
    string extraInfo;

    if (!(cin >> craftName) || !(cin >> craftType) || !(cin >> strength)){
        throw invalidInputException();
    }

    parseLocation(point,cin);

    if (!(getline(cin,extraInfo))){
        throw invalidInputException();
    }

    Model::getInstance().addCraft(craftName,craftType,point,strength,extraInfo);
}

Controller::Controller() : view(make_shared<View>()){
}

void Controller::createPorts(ifstream &inputFile) {

    if (!inputFile.is_open()){
        throw invalidPortFileException();
    }

    string portName;
    string portLocationString;
    double initialPortFuel;
    double hourlyFuelProduction;
    char c;
    Point portLocation;

    while (inputFile >> portName &&
           inputFile >> c && inputFile >> portLocation.x  &&
            inputFile >> c && inputFile >> portLocation.y && inputFile >> c &&
           inputFile >> initialPortFuel && inputFile >> hourlyFuelProduction) {
        try {
            Model::getInstance()
                    .addPort(portName, portLocation, initialPortFuel, hourlyFuelProduction);
        } catch (exception &e) {
            throw e;
        }
    }

}

