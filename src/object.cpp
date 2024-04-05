#include "object.h"
#include <cmath>
#include <iostream>

Object::Object(const std::string& n, std::vector<double>& pos, std::vector<double>& spd,
std::vector<double>& acc, double m) : name(n), position(pos),
speed(spd), acceleration(acc), mass(m)
{
    this->name = n;
    this->position = pos;
    this->speed = spd;
    this->acceleration = acc;
    this->mass = m;

}

std::string Object::getName() const {
    return name;
}

std::vector<double> Object::getPosition() const {
    return position;
}

std::vector<double> Object::getSpeed() const {
    return speed;
}

std::vector<double> Object::getAcceleration() const {
    return acceleration;
}

double Object::getMass() const {
    return mass;
}

void Object::setName(const std::string& n) {
    name = n;
}

void Object::setPosition(std::vector<double>& pos) {
    position = pos;
}

void Object::setSpeed(std::vector<double>& spd) {
    speed = spd;
}

void Object::setAcceleration(std::vector<double>& acc) {
    acceleration = acc;
} 

void Object::setMass(double m) {
    mass = m;
}

std::vector<double> Object::gravForce(const Object& obj) {
    std::cout << "distance : " << distance(obj) << std::endl;
    double cos_theta = (obj.getPosition()[0] - position[0]) / sqrt(pow(obj.getPosition()[0] - position[0], 2) + 
                                                                    pow(obj.getPosition()[1] - position[1], 2));
    double sin_theta = (obj.getPosition()[1] - position[1]) / sqrt(pow(obj.getPosition()[0] - position[0], 2) + 
                                                                    pow(obj.getPosition()[1] - position[1], 2));
    double cos_phi = (obj.getPosition()[2] - position[2]) / distance(obj);
    double sin_phi = sqrt(1 - cos_phi * cos_phi);
    std::vector<double> force;
    force.push_back((6.67408E-11 * mass * obj.getMass() * cos_theta * sin_phi) / pow(distance(obj), 2));
    force.push_back((6.67408E-11 * mass * obj.getMass() * sin_theta * sin_phi) / pow(distance(obj), 2));
    force.push_back((6.67408E-11 * mass * obj.getMass() * cos_phi) / pow(distance(obj), 2));
    return force;
}

double Object::distance(const Object& obj){
    std::vector<double> objPosition = obj.getPosition();
    return(sqrt(pow(position[0]-objPosition[0],2)+
            pow(position[1]-objPosition[1],2)+
            pow(position[2]-objPosition[2],2)));
}

double Object::kineticEnergy() {
    double kinetic = 0.5 * mass * (speed[0] * speed[0] + speed[1] * speed[1] + speed[2] * speed[2]);
    return kinetic;
}

void Object::potentialEnergy(Object obj) {
    double potential = sqrt(gravForce(obj)[0] * gravForce(obj)[0] +
                            gravForce(obj)[1] * gravForce(obj)[1] +
                            gravForce(obj)[2] * gravForce(obj)[2])*mass*
                            distance(obj);
    potentialEnergyVect.push_back(potential);
}

void Object::clearPotentialEnergy() {
    potentialEnergyVect.clear();
}

double Object::totalEnergy(Object obj) {
    double potEnergy;
    for (int i = 0; i < potentialEnergyVect.size(); i++) {
        potEnergy += potentialEnergyVect[i];
    }
    double total = kineticEnergy() + potEnergy;
    return total;
}


