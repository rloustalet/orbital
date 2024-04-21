//
#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <string>
#include <vector>
#include <cmath>
#include "time.h"
#include "object.h"

using namespace std;

#define PBSTR "|||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 50

class SolarSystem {
    private:
        string name;
        vector<Object> objects; 
        double processMass(const string& response);
        vector<double> processPosition(const string& response);
        vector<double> processSpeed(const string& response);
        void printProgress(double percentage, int iterations_so_far, int total_iterations);

    public:
        SolarSystem(const string& n);
        void solve(string algo, double h, double t, bool export_data = true);
        void exportdata(Object obj, double time);
        void verlet(Object& obj1, vector<Object> objects, double h);
        void RK4(Object& obj1, vector<Object> objects, double h);
        void euler(Object& obj1, vector<Object> objects, double h);
        void addObjectFromHorizons(string name);
        vector<Object> getObjects();
        double totalEnergy();
        void addObject(string name, vector<double> position, vector<double> speed, vector<double> acceleration, double mass);

        

};

#endif






