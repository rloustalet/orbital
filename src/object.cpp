#include "object.h"
#include "util.h"

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

double Object::gravForce(const Object& obj) {
    double force = -6.67408E-11 * mass * obj.getMass() / distance(obj) / distance(obj);
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

double Object::potentialEnergy(const Object& obj) {
    double potential = -6.67408E-11 * mass / distance(obj) / distance(obj);
    return potential;
}


