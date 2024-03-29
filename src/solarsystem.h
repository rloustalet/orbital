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
        double fonctionvitesse(double force,double t,double m,double vitesseinit);

    public:
        SolarSystem(const string& n,const vector<Object>& objects); //on a dit que c t des arg de la classe SolarSystem
        void solve(string algo, double h, double t);
        void exportdata(Object obj);
        void verlet(Object& obj1, Object obj2, double h);
        void RK4(Object& obj1, Object obj2, double h, double t);
        

};

#endif






