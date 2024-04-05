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
    std::vector<double> distVect = distanceVect(obj);
    std::vector<double> force(3);
    force[0] -= 6.67408E-11 * mass * obj.getMass() * distVect[0] / pow(distance(obj), 3);
    force[1] -= 6.67408E-11 * mass * obj.getMass() * distVect[1] / pow(distance(obj), 3);
    force[2] -= 6.67408E-11 * mass * obj.getMass() * distVect[2] / pow(distance(obj), 3);
    return force;
}

void Object::computeAcceleration(std::vector<Object>& objects) {
    std::vector<double> accel(3);
    for(Object obj : objects) {
        for (int l = 0; l<=2; l++) {
            accel[l] += gravForce(obj)[l] / mass;
        }
    }
    setAcceleration(accel);
}

std::vector<double> Object::distanceVect(Object obj) {
    std::vector<double> objPosition = obj.getPosition();
    std::vector<double> distanceVect;
    distanceVect.push_back(position[0] - objPosition[0]);
    distanceVect.push_back(position[1] - objPosition[1]);
    distanceVect.push_back(position[2] - objPosition[2]);
    return distanceVect;
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

void Object::computePotentialEnergy(std::vector<Object>& objects) {
    double potential;
    for (Object obj : objects) {
        potentialEnergy +=sqrt(gravForce(obj)[0] * gravForce(obj)[0] +
                            gravForce(obj)[1] * gravForce(obj)[1] +
                            gravForce(obj)[2] * gravForce(obj)[2])*mass*
                            distance(obj);
    }
}

void Object::clearPotentialEnergy() {
    potentialEnergy = 0;
}

double Object::totalEnergy() {
    double total = kineticEnergy() + potentialEnergy;
    return total;
}


