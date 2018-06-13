//
// Created by amichai on 11/06/18.
//

#include "Controller.h"

void Controller::run() {
    string input;

    cout << "Time " << Model::getInstance().getTime() << ": ";
    cout << "Enter command: ";

    cin >> input;

    while (getQuery(input) != quit){
        try {
            switch (getQuery(input)) {
                case defaultMap:
                    view->restoreDefault();
                    break;
                case changeMapSize:
                    int size;
                    cin >> size;

                    if (cin.fail()){
                        throw invalidMapSize();
                    }
                    view->setDisplaySize(size);

                    break;
                case zoomMap:{
                    double scale;
                    cin >> scale;

                    if (cin.fail()){
                        throw invalidScaleException();
                    }

                    view->setScale(scale);
                } break;
                case panMap: {
                    Point p;
                    cin >> p.x;
                    cin >> p.y;

                    if (cin.fail()) {
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
                case createSeacraft: {
                    addSeacraft();
                } break;
                case course:
                    break;
                case position:
                    break;
                case destination:
                    break;
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
            }
        } catch (exception &e){
            cin.ignore(INT32_MAX,'\n');
            cerr << e.what() << endl;
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

void Controller::parseLocation(Point &p) {
    char c;

    cin >> c;           //'('
    cin >> p.x;           //'double'
    if (cin.fail() || c != '('){
        throw invalidLocationException();
    }

    cin >> c;       //','
    cin >> p.y;       //'double'
    if (cin.fail() || c != ','){
        throw invalidLocationException();
    }

    cin >> c;   //')'
    if (c != ')'){
        throw invalidLocationException();
    }
}

crafts Controller::getSeacraftType(string s) {
    if (s == "Cruiser") return cruiser;
    if (s == "Freighter") return freighter;
    if (s == "Patrol_boat") return patrol_boat;
    return invalidCraft;
}

void Controller::addSeacraft() {
    string craftName;
    string craftType;
    Point point;
    int strength;
    string extraInfo;

    cin >> craftName;
    cin >> craftType;
    parseLocation(point);
    cin >> strength;
    getline(cin,extraInfo);

    switch (getSeacraftType(craftType)) {
        case cruiser:
            Model::getInstance().addCraft(shared_ptr<Seacraft>(new Cruiser(craftName, point, strength)));
            break;
        case freighter:
            if (extraInfo.empty()) {
                Model::getInstance().addCraft(shared_ptr<Seacraft>(new Freighter(craftName, point, strength)));
            } else {
                Model::getInstance().addCraft(shared_ptr<Seacraft>(new Freighter(craftName, point, strength, stoi(extraInfo)))); break;
            }
            break;
        case patrol_boat:
            if (extraInfo.empty()) {
                Model::getInstance().addCraft(shared_ptr<Seacraft>(new PatrolBoat(craftName, point, strength))); break;
            }
            break;
        default:
            throw invalidCraftFormat();
    }
}

Controller::Controller() : view(make_shared<View>()){
}

