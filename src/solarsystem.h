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
        std::vector<double> processPosition(const string& response);
        std::vector<double> processSpeed(const string& response);
        void printProgress(double percentage);

    public:
        SolarSystem(const string& n,const vector<Object>& objects); //on a dit que c t des arg de la classe SolarSystem
        void solve(string algo, double h, double t);
        void exportdata(Object obj);
        void verlet(Object& obj1, vector<Object> objects, double h);
        void RK4(Object& obj1, vector<Object> objects, double h);
        bool isStar(Object* obj);
        void addObjectFromHorizons(string name);
        std::vector<Object> getObjects();

        

};

#endif






