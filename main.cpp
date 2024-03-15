#include <vector>
#include "src/object.h"
#include "src/solarsystem.h"

int main(){
    double h = 12 * 3600;
    double t = 365 * 24 * 3600;

    std::vector<double> positionSun;
    positionSun.push_back(0);
    positionSun.push_back(0);
    positionSun.push_back(0);

    std::vector<double> positionEarth;
    positionEarth.push_back(147098290E3);
    positionEarth.push_back(0);
    positionEarth.push_back(0);

    std::vector<double> speedEarth;
    speedEarth.push_back(0);
    speedEarth.push_back(30287);
    speedEarth.push_back(0);

    std::vector<double> speedSun;
    speedSun.push_back(0);
    speedSun.push_back(0);
    speedSun.push_back(0);

    std::vector<double> acceleration;
    acceleration.push_back(0);
    acceleration.push_back(0);
    acceleration.push_back(0);
    
    Object sun("Sun", positionSun, speedSun, acceleration, 1.9891E30);
    Object earth("Earth", positionEarth, speedEarth, acceleration, 5.9736E24);

    std::vector<Object> objects;
    objects.push_back(sun);
    objects.push_back(earth);

    SolarSystem solarsystem("système solaire",objects);
    solarsystem.solve(h, t);//une demi journée en pas et 365j

}

