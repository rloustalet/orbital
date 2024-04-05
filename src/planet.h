#ifndef PLANET_H
#define PLANET_H
#include "object.h"

class Planet : public Object {
    protected:
        double areat;
    public:
        Planet();
        Planet(const std::string& name, std::vector<double>& position, std::vector<double>& speed,
           std::vector<double>& acceleration, double mass);
        double area();
};
#endif