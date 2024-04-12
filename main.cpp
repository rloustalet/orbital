#include <vector>
#include <iostream>
#include <string>
#include "src/object.h"
#include "src/solarsystem.h"

int main(){
    long int h = 1 * 24 * 3600L;
    long int t =  30 * 365 * 24 * 3600L;

    std::vector<Object> objects;


    SolarSystem solarsystem("solar_system",objects);
    solarsystem.addObjectFromHorizons("Sun");
    solarsystem.addObjectFromHorizons("Mercury");
    solarsystem.addObjectFromHorizons("Venus");
    solarsystem.addObjectFromHorizons("Earth");
    solarsystem.addObjectFromHorizons("Mars");
    solarsystem.addObjectFromHorizons("Jupiter");
    solarsystem.addObjectFromHorizons("Saturn");
    //solarsystem.addObjectFromHorizons("Uranus");
    //solarsystem.addObjectFromHorizons("Neptune");
    //solarsystem.addObjectFromHorizons("moon");
    //solarsystem.addObjectFromHorizons("io");
    //solarsystem.addObjectFromHorizons("europa");
    //solarsystem.addObjectFromHorizons("ganymede");
    //solarsystem.addObjectFromHorizons("callisto");
    
    
    solarsystem.solve("RK4",h, t);

}

