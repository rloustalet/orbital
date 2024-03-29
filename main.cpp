#include <vector>
#include <iostream>
#include "src/object.h"
#include "src/solarsystem.h"

int main(){
    double h = 0.5 * 3600;
    double t = 1 * 365 * 24 * 3600;

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

    std::vector<double> accelerationSun;
    accelerationSun.push_back(0);
    accelerationSun.push_back(1.84E-8);
    accelerationSun.push_back(0);

    std::vector<double> accelerationEarth;
    accelerationEarth.push_back(0);
    accelerationEarth.push_back(-6.1315E-3);
    accelerationEarth.push_back(0);
    
    Object sun("Sun", positionSun, speedSun, accelerationSun, 1.9891E30);
    Object earth("Earth", positionEarth, speedEarth, accelerationEarth, 5.9736E24);

    double force = 6.67408E-11 * sun.getMass() * earth.getMass() / pow(earth.distance(sun), 2);
    std::cout << force << std::endl;

    std::vector<Object> objects;
    objects.push_back(sun);
    objects.push_back(earth);

    SolarSystem solarsystem("système solaire",objects);
    solarsystem.solve("RK4",h, t);//une demi journée en pas et 365j

}

