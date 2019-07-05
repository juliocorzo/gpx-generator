#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Coordinates {
    string lat;
    string lon;
};

void verifyFile(int argc);
void buildCoordinates(vector<Coordinates> &c, const string &f);
void printCoordinates(vector<Coordinates> &c);
void generateGPX(vector<Coordinates> &c);

int main(int argc, char* argv[]) {
    verifyFile(argc);
    vector<Coordinates> c;
    buildCoordinates(c, argv[1]);
    printCoordinates(c);
    generateGPX(c);

}

void generateGPX(vector<Coordinates> &c) {
    ofstream o;
    o.open("output.gpx");

    string code;
    code += R"(<?xml version="1.0" encoding="UTF-8"?>)"; code += "\n";
    code += R"(<gpx xmlns="http://www.topografix.com/GPX/1/1" version="1.1" creator="iSpoofer">)"; code += "\n";
    code += R"( <trk>)"; code += "\n";
    code += R"(     <name>0</name>)"; code += "\n";
    code += R"(     <trkseg>)"; code += "\n";

    for(auto & x : c) {
        code += "\t\t";
        code += R"(<trkpt lat=")"; code += x.lat;
        code += R"(" lon=")"; code += x.lon;
        code += R"(">)"; code += "\n";
        code += "\t\t"; code += R"(</trkpt>)"; code += "\n";
    }

    code += R"(     </trkseg>)"; code += "\n";
    code += R"( </trk>)"; code += "\n";
    code += R"(</gpx>)"; code += "\n";

    o << code;
}

void printCoordinates(vector<Coordinates> &c) {
    for(auto & x : c)
        cout << x.lat << " " << x.lon << endl;
}

void buildCoordinates(vector<Coordinates> &c, const string &f) {
    ifstream input(f.c_str());
    string currentCoordinate;

    while(getline(input, currentCoordinate)) {
        string coordinate;
        vector<string> location;
        stringstream ss(currentCoordinate);

        while(getline(ss, coordinate, ',')) {
            if(coordinate[0] == ' ') coordinate.erase(0,1);
        location.push_back(coordinate);
        }
        Coordinates temp = {location[0], location[1]};
        c.push_back(temp);
    }
}

void verifyFile(int argc) {
    if(argc == 2) return;
    cout << "The input file was not found, please try again" << endl;
    exit(EXIT_FAILURE);
}