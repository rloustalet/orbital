#ifndef STAR_H
#define STAR_H
#include "object.h"

class Star : public Object {
    protected:
        double areat;
    public:
        Star();
        Star(const std::string& name, std::vector<double>& position, std::vector<double>& speed,
           std::vector<double>& acceleration, double mass);
        };
#endif