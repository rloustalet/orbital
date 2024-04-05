#include <vector>
#include <iostream>
#include <string>
#include "src/object.h"
#include "src/solarsystem.h"
#include "src/planet.h"
#include "src/star.h"

int main(){
    double h = 0.5 * 3600;
    double t =  20 * 365 * 24 * 3600;

    std::vector<double> positionSun;
    positionSun.push_back(0);
    positionSun.push_back(0);
    positionSun.push_back(0);

    std::vector<double> positionEarth;
    positionEarth.push_back(147098290E3);
    positionEarth.push_back(0);
    positionEarth.push_back(0);

    std::vector<double> positionJupiter;
    positionJupiter.push_back(778500000E3);
    positionJupiter.push_back(0);
    positionJupiter.push_back(0);

    std::vector<double> positionSaturn;
    positionSaturn.push_back(1433500000E3);
    positionSaturn.push_back(0);
    positionSaturn.push_back(0);

    std::vector<double> speedEarth;
    speedEarth.push_back(0);
    speedEarth.push_back(30287);
    speedEarth.push_back(0);

    std::vector<double> speedSun;
    speedSun.push_back(0);
    speedSun.push_back(0);
    speedSun.push_back(0);

    std::vector<double> speedJupiter;
    speedJupiter.push_back(0);
    speedJupiter.push_back(13.0585E3);
    speedJupiter.push_back(0);

    std::vector<double> speedSaturn;
    speedSaturn.push_back(0);
    speedSaturn.push_back(9.69E3);
    speedSaturn.push_back(0);

    std::vector<double> accelerationSun;
    accelerationSun.push_back(0);
    accelerationSun.push_back(0);
    accelerationSun.push_back(0);

    std::vector<double> accelerationEarth;
    accelerationEarth.push_back(0);
    accelerationEarth.push_back(0);
    accelerationEarth.push_back(0);

    std::vector<double> accelerationJupiter;
    accelerationJupiter.push_back(0);
    accelerationJupiter.push_back(0);
    accelerationJupiter.push_back(0);

    std::vector<double> accelerationSaturn;
    accelerationSaturn.push_back(0);
    accelerationSaturn.push_back(0);
    accelerationSaturn.push_back(0);


    
    Star sun("Sun", positionSun, speedSun, accelerationSun, 1.9891E30);
    Planet earth("Earth", positionEarth, speedEarth, accelerationEarth, 5.9736E24);
    Planet jupiter("Jupiter", positionJupiter, speedJupiter, accelerationJupiter, 1.8986E27);
    Planet saturn("Saturn", positionSaturn, speedSaturn, accelerationSaturn, 5.6834E26);

    double force = 6.67408E-11 * sun.getMass() * earth.getMass() / pow(earth.distance(sun), 2);
    std::cout << force << std::endl;

    std::vector<Object> objects;
    objects.push_back(sun);
    objects.push_back(earth);
    objects.push_back(jupiter);
    objects.push_back(saturn);

    SolarSystem solarsystem("système solaire",objects);
    solarsystem.solve("rk4",h, t);

}

