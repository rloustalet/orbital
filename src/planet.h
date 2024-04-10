#ifndef PLANET_H
#define PLANET_H
#include "object.h"
#include "star.h"

using namespace std;

class Planet : public Object {
    protected:
        double areat;
    public:
        Planet();
        Planet(const string& n, vector<double>& pos, vector<double>& spd,
vector<double>& acc, double m);
        double area(Star star,double t);
        double normeCinematicMoment(Star star);
};
#endif