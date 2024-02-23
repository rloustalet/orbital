#include "../src/object.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<double> position;
    position.push_back(0);
    position.push_back(0);
    position.push_back(0);

    std::vector<double> speed;
    speed.push_back(0);
    speed.push_back(0);
    speed.push_back(0);

    std::vector<double> acceleration;
    acceleration.push_back(0);
    acceleration.push_back(0);
    acceleration.push_back(0);
    
    Object sun("Sun", position, speed, acceleration, 1.9891E30);
    Object earth("Earth", position, speed, acceleration, 5.9736E24);
    std::cout << earth.getMass() << std::endl;
}