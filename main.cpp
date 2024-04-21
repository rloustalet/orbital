#include <vector>
#include <iostream>
#include <string>
#include "src/object.h"
#include "src/solarsystem.h"

int main(){

    SolarSystem solarsystem("solar_system"); //Cette ligne => on instancie la classe SolarSystem

    vector<double> positionEarth; // on crée le vecteur positionEarth
    positionEarth.push_back(147098290E3);
    positionEarth.push_back(0);
    positionEarth.push_back(0);

    vector<double> positionSun; // on crée le vecteur positionSun
    positionSun.push_back(0);
    positionSun.push_back(0);
    positionSun.push_back(0);

    vector<double> speedEarth; // on crée le vecteur speedEarth
    speedEarth.push_back(0);
    speedEarth.push_back(30287);
    speedEarth.push_back(0);

    vector<double> speedSun; // on crée le vecteur speedSun
    speedSun.push_back(0);
    speedSun.push_back(0);
    speedSun.push_back(0);

    vector<double> accelEarth; // on crée le vecteur accelEarth
    accelEarth.push_back(0);
    accelEarth.push_back(0);
    accelEarth.push_back(0);

    vector<double> accelSun; // on crée le vecteur accelSun
    accelSun.push_back(0);
    accelSun.push_back(0);
    accelSun.push_back(0);

    //long int h = 0.001 * 24 * 3600L; // pas de temps
    double h=60;
    long int t =  130 * 365 * 24 * 3600L; // temps d'intégartion

    solarsystem.addObject("Sun", positionSun, speedSun, accelSun, 1.9891E30); // on ajoute les objets au système par les vecteurs
    solarsystem.addObject("Earth", positionEarth, speedEarth, accelEarth, 5.9736E24);
    
    //solarsystem.addObjectFromHorizons("Sun"); // on ajoute les objets au système par les noms et une requête à Horizons
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
    
    
    solarsystem.solve("rk4",h, t); // on appelle la fonction solve

}

