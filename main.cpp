#include <vector>
#include <iostream>
#include <string>
#include "src/object.h"
#include "src/solarsystem.h"

int main(){
    vector<double> positionEarth;
    positionEarth.push_back(147098290E3);
    positionEarth.push_back(0);
    positionEarth.push_back(0);

    vector<double> positionSun;
    positionSun.push_back(0);
    positionSun.push_back(0);
    positionSun.push_back(0);

    vector<double> speedEarth;
    speedEarth.push_back(0);
    speedEarth.push_back(30287);
    speedEarth.push_back(0);

    vector<double> speedSun;
    speedSun.push_back(0);
    speedSun.push_back(0);
    speedSun.push_back(0);

    vector<double> accelEarth;
    accelEarth.push_back(0);
    accelEarth.push_back(0);
    accelEarth.push_back(0);

    vector<double> accelSun;
    accelSun.push_back(0);
    accelSun.push_back(0);
    accelSun.push_back(0);

    long int h = 0.001 * 24 * 3600L;
    long int t =  1 * 365 * 24 * 3600L;

    SolarSystem solarsystem("solar_system");
    solarsystem.addObject("Sun", positionSun, speedSun, accelSun, 1.9891E30);
    solarsystem.addObject("Earth", positionEarth, speedEarth, accelEarth, 5.9736E24);
    
    //solarsystem.addObjectFromHorizons("Sun");
    //solarsystem.addObjectFromHorizons("Mercury");
    //solarsystem.addObjectFromHorizons("Venus");
    //solarsystem.addObjectFromHorizons("Earth");
    //solarsystem.addObjectFromHorizons("Mars");
    //solarsystem.addObjectFromHorizons("Jupiter");
    //solarsystem.addObjectFromHorizons("Saturn");
    //solarsystem.addObjectFromHorizons("Uranus");
    //solarsystem.addObjectFromHorizons("Neptune");
    //solarsystem.addObjectFromHorizons("moon");
    //solarsystem.addObjectFromHorizons("io");
    //solarsystem.addObjectFromHorizons("europa");
    //solarsystem.addObjectFromHorizons("ganymede");
    //solarsystem.addObjectFromHorizons("callisto");
    
    
    solarsystem.solve("verlet",h, t);

}

