//
// Created by amichai on 11/06/18.
//

#include "Controller.h"

const string Controller::INITIAL_PORT = "Nagoya (50,5) 1000000 1000";

void Controller::run(ifstream &inputFile) {
    string input;

    createPorts(inputFile);

    cout << "Time " << Model::getInstance().getTime() << ": ";
    cout << "Enter command: ";
    cin >> input;

    while (getQuery(input) != quit){
        try {

            switch (getQuery(input)) {
                case defaultMap:
                    view->restoreDefault();
                    break;
                case changeMapSize: {
                    int size;
                    cin >> size;

                    view->setDisplaySize(size);
                } break;
                case zoomMap:{
                    double scale;

                    cin >> scale;

                    view->setScale(scale);
                } break;
                case panMap: {
                    Point p;
                    cin >> p.x;
                    cin >> p.y;
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
                    if (!Model::getInstance().seacraftExists(input)){
                        cerr << "ERROR: Invalid query. try again:" << endl;

                        break;
                    }
                    seacraftOptions(input);
                }
            }
        } catch (exception &e){
            cerr << e.what() << endl;
            cin.clear();
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
    is >> c;
    is >> p.x;

    if (is.fail() || c != '('){
        throw invalidLocationException();
    }

    is >> c;
    is >> p.y;

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

    cin >> craftName;
    cin >> craftType;

    parseLocation(point,cin);

    cin >> strength;

    getline(cin,extraInfo);

    if (Model::getInstance().seacraftExists(craftName)){
        throw invalidCraftNameException();
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
    stringstream ss;
    ss << INITIAL_PORT;

    ss >> portName >> c >> portLocation.x >> c
       >> portLocation.y >> c >> initialPortFuel >>hourlyFuelProduction;

    Model::getInstance().addPort(portName, portLocation, initialPortFuel, hourlyFuelProduction);

    while (inputFile >> portName &&
           inputFile >> c && inputFile >> portLocation.x  &&
           inputFile >> c && inputFile >> portLocation.y && inputFile >> c &&
           inputFile >> initialPortFuel && inputFile >> hourlyFuelProduction) {
        Model::getInstance().addPort(portName,
                                     portLocation, initialPortFuel, hourlyFuelProduction);

    }

}

void Controller::seacraftOptions(const string &seacraftName) {
    string input;

    cin >> input;
    switch (getQuery(input)){
        case course:{
            double degree;
            double speed;

            cin >> degree;

            cin >> speed;

            Model::getInstance().setCourse(seacraftName, degree, speed);
        } break;
        case position:{
            Point p;
            double speed;

            parseLocation(p,cin);
            cin >> speed;

            Model::getInstance().setPosition(seacraftName, p, speed);
        } break;
        case destination: {
            string portName;
            double speed;

            cin >> portName;
            cin >> speed;

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
            cin.clear();
            cin.ignore(INT32_MAX,'\n');
            break;

    }
}

