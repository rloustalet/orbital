#include <vector>
#include <iostream>
#include <string>
#include "src/object.h"
#include "src/solarsystem.h"
#include "src/planet.h"
#include "src/star.h"

int main(){
    long int h = 3 * 24 * 3600L;
    long int t =  90 * 365 * 24 * 3600L;

    std::vector<Object> objects;
    //objects.push_back(sun);
    //objects.push_back(earth);
    //objects.push_back(jupiter);
    //objects.push_back(saturn);


    SolarSystem solarsystem("système solaire",objects);
    solarsystem.addObjectFromHorizons("Sun");
    solarsystem.addObjectFromHorizons("Mercury");
    solarsystem.addObjectFromHorizons("Venus");
    solarsystem.addObjectFromHorizons("Earth");
    solarsystem.addObjectFromHorizons("Mars");
    solarsystem.addObjectFromHorizons("Jupiter");
    solarsystem.addObjectFromHorizons("Saturn");
    solarsystem.addObjectFromHorizons("Uranus");
    solarsystem.addObjectFromHorizons("Neptune");
    //solarsystem.addObjectFromHorizons("Pluto");
    //solarsystem.addObjectFromHorizons("moon");
    
    
    solarsystem.solve("rk4",h, t);

}

