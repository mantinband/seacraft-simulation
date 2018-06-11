//
// Created by amichai on 11/06/18.
//

#include "Controller.h"

void Controller::initiate() {
    string input;

    cout << "Time " << Model::getInstance().getTime() << ": ";
    cout << "Enter command: ";

    cin >> input;

    while (getQuery(input) != quit){
        try {
            switch (getQuery(input)) {
                case defaultMap:
                    break;
                case changeMapSize:
                    break;
                case zoomMap:
                    break;
                case panMap:
                    break;
                case showMap:
                    view.lock()->show();
                    break;
                case showStatus:
                    break;
                case incrementTime:
                    break;
                case createSeacraft: {
                    shared_ptr<Seacraft> seacraftToAdd = getSeacraft();
                    Model::getInstance().addCraft(seacraftToAdd);
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
                    break;
            }
            cout << "Time " << Model::getInstance().getTime() << ": ";
            cout << "Enter command: ";

            cin >> input;

        } catch (exception &e){
            cerr << e.what() << endl;
        }
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

void Controller::parseLocation(double &x, double &y) {
    char c;

    cin >> c;           //'('
    cin >> x;           //'double'
    if (cin.fail() || c != '('){
        throw invalidLocationException();
    }

    cin >> c;       //','
    cin >> y;       //'double'
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

shared_ptr<Seacraft> Controller::getSeacraft() {
    string craftName;
    string craftType;
    double x, y;
    int strength;
    string extraInfo;

    cin >> craftName;
    cin >> craftType;
    parseLocation(x, y);
    cin >> strength;
    getline(cin,extraInfo);


    switch (getSeacraftType(craftType)) {
        case cruiser:
            if (extraInfo.empty()) {
                return make_shared<Cruiser>(craftName, x, y, strength);
            } else {
                return make_shared<Cruiser>(craftName, x, y, strength, stoi(extraInfo));
            }
        case freighter:
            if (extraInfo.empty()) {
                return make_shared<Freighter>(craftName, x, y, strength);
            } else {
                return make_shared<Freighter>(craftName, x, y, strength, stoi(extraInfo));
            }
        case patrol_boat:
            if (extraInfo.empty()) {
                return make_shared<PatrolBoat>(craftName, x, y, strength);
            } else {
                return make_shared<PatrolBoat>(craftName, x, y, strength, stoi(extraInfo));
            }
        default:
            throw invalidCraftFormat();
    }
}

Controller::Controller(const shared_ptr<View> &view) : view (view){
}

