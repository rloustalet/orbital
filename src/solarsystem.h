//
#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <string>
#include <vector>
#include <cmath>
#include "object.h"

using namespace std;

class SolarSystem {
    private:
        string name;
        vector<Object> objects; 

    public:
        SolarSystem(const string& n,const vector<Object>& objects); //on a dit que c t des arg de la classe SolarSystem
        void solve(double h, double t);


};

#endif






