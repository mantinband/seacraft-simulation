//
// Created by amichai on 11/06/18.
//

#include "Controller.h"

const string Controller::INITIAL_PORT = "Nagoya (50,5) 1000000 1000";

Controller::Controller() : view(make_shared<View>()){
}


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
                } break;
                case showMap:
                    view->show();
                    break;
                case showStatus:
                    cout << Model::getInstance().getStatus();
                    break;
                case createSeacraft:
                    addSeacraft();
                    break;
                case go:
                    Model::getInstance().update();
                    break;
                default: {
                    /*  if first token is not one of the querys above and not
                     * a seacraft name print error message and break    */
                    if (!Model::getInstance().seacraftExists(input)){
                        cerr << "ERROR: Invalid query. try again:" << endl;
                        cin.clear();
                        cin.ignore(INT32_MAX,'\n');
                        break;
                    }
                    /*  go to seacraft options  */
                    seacraftOptions(input);
                }
            }
        } catch (exception &e){
            cerr << e.what() << endl;
            /*  clear input buffer  */
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
    if (s == "go") return go;
    if (s == "create") return createSeacraft;

    if (s == "course") return course;
    if (s == "position") return position;
    if (s == "destination") return destination;
    if (s == "load_at") return load_at;
    if (s == "unload_at") return unload_at;
    if (s == "dock_at") return dock_at;
    if (s == "attack") return attackSeacraft;
    if (s == "refuel") return refuelSeacraft;
    if (s == "stop") return stopSeacraft;

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

    if (Model::getInstance().seacraftExists(craftName)){
        throw invalidCraftNameException();
    }

    cin >> craftType;

    parseLocation(point,cin);

    cin >> strength;

    getline(cin,extraInfo);

    /*  send data to the model's factory    */
    Model::getInstance().addCraft(craftName,craftType,point,strength,extraInfo);
}

void Controller::createPorts(ifstream &inputFile) {
    if (!inputFile.is_open()){
        throw invalidPortFileException();
    }

    string portName;
    string portLocationString;
    double hourlyFuelProduction;
    double initialPortFuel;
    char c;
    Point portLocation;
    stringstream ss;

    /*  create defualt port */
    ss << INITIAL_PORT;

    ss >> portName >> c >> portLocation.x >> c
       >> portLocation.y >> c >> initialPortFuel >>hourlyFuelProduction;

    Model::getInstance().addPort(portName, portLocation, initialPortFuel, hourlyFuelProduction);

    /*  read ports from file    */
    while (inputFile >> portName &&
           inputFile >> c && inputFile >> portLocation.x  &&
           inputFile >> c && inputFile >> portLocation.y && inputFile >> c &&
           inputFile >> initialPortFuel && inputFile >> hourlyFuelProduction) {
        Model::getInstance().addPort(portName,
                                     portLocation, initialPortFuel, hourlyFuelProduction);

    }

}

void Controller::seacraftOptions(string seacraftName) {
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

        case load_at: {
            string portDestination;
            cin >> portDestination;
            Model::getInstance().addLoadDestination(seacraftName, portDestination);
        } break;

        case unload_at: {
            string portDestination;
            int numOfContainersToUnload;
            cin >> portDestination >> numOfContainersToUnload;
            Model::getInstance().addUnloadDestination(seacraftName, portDestination, numOfContainersToUnload);
        } break;

        case dock_at: {
            string portDestination;
            cin >> portDestination;
            Model::getInstance().setDockingPort(seacraftName, portDestination);
        } break;

        case attackSeacraft: {
            string pirateShipName = seacraftName;
            cin >> seacraftName;
            Model::getInstance().attackSeacraft(pirateShipName, seacraftName);
            break;
        }

        case refuelSeacraft:
            Model::getInstance().refuelCraft(seacraftName);
            break;

        case stopSeacraft:
            Model::getInstance().stopSeacraft(seacraftName);
            break;

        default:
            cerr << "ERROR: Invalid query. try again:" << endl;
            /*  clear input buffer  */
            cin.clear();
            cin.ignore(INT32_MAX,'\n');
            break;

    }
}

