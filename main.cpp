#include <vector>
#include <iostream>
#include "src/object.h"
#include "src/solarsystem.h"
#include "src/planet.h"
#include "src/star.h"

int main(){
    double h = 0.5 * 3600;
    double t =  2 * 365 * 24 * 3600;

    std::vector<double> positionSun;
    positionSun.push_back(-1.068108951496322E9);
    positionSun.push_back(-4.177210908491462E8);
    positionSun.push_back(3.086887010002915E7);

    std::vector<double> positionEarth;
    positionEarth.push_back(-2.627903751048988E10);
    positionEarth.push_back(1.445101984929515E11);
    positionEarth.push_back(3.025245352813601E7);

    std::vector<double> positionJupiter;
    positionJupiter.push_back(778500000E3);
    positionJupiter.push_back(0);
    positionJupiter.push_back(0);

    std::vector<double> positionSaturn;
    positionSaturn.push_back(1433500000E3);
    positionSaturn.push_back(0);
    positionSaturn.push_back(0);

    std::vector<double> speedEarth;
    speedEarth.push_back(-2.983052803412253E4);
    speedEarth.push_back(-5.220465675237847E3);
    speedEarth.push_back(-1.014855999592612E-1);

    std::vector<double> speedSun;
    speedSun.push_back(9.305302656256911);
    speedSun.push_back(-1.283177282717393E1);
    speedSun.push_back(-1.631700118015769E-1);

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
    accelerationEarth.push_back(speedEarth[1] * speedEarth[1] / positionEarth[0]);
    accelerationEarth.push_back(0);

    std::vector<double> accelerationJupiter;
    accelerationJupiter.push_back(0);
    accelerationJupiter.push_back(speedJupiter[1] * speedJupiter[1] / positionJupiter[0]);
    accelerationJupiter.push_back(0);

    std::vector<double> accelerationSaturn;
    accelerationSaturn.push_back(0);
    accelerationSaturn.push_back(speedSaturn[1] * speedSaturn[1] / positionSaturn[0]);
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
    //objects.push_back(jupiter);
    //objects.push_back(saturn);

    SolarSystem solarsystem("système solaire",objects);
    solarsystem.solve("RK4",h, t);//une demi journée en pas et 365j

}

