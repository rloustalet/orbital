#include "../src/object.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<double> positionSun;
    positionSun.push_back(0);
    positionSun.push_back(0);
    positionSun.push_back(0);

    std::vector<double> positionEarth;
    positionEarth.push_back(147098290E3);
    positionEarth.push_back(0);
    positionEarth.push_back(0);

    std::vector<double> speed;
    speed.push_back(0);
    speed.push_back(0);
    speed.push_back(0);

    std::vector<double> acceleration;
    acceleration.push_back(0);
    acceleration.push_back(0);
    acceleration.push_back(0);
    
    Object sun("Sun", positionSun, speed, acceleration, 1.9891E30);
    Object earth("Earth", positionEarth, speed, acceleration, 5.9736E24);
    std::cout << earth.getMass() << std::endl;

    std::cout << earth.gravForce(sun) << std::endl; // Ici c'est l'argument qui exerce la force de gravité

    std::cout << "distance = " << earth.distance(sun) << std::endl;
}