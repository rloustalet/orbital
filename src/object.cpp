#include "object.h"
#include <cmath>
#include <iostream>

/**
 * Constructor for Object class.
 *
 * @param n the name of the object
 * @param pos the initial position of the object
 * @param spd the initial speed of the object
 * @param acc the initial acceleration of the object
 * @param m the mass of the object
 *
 * @return N/A
 *
 * @throws N/A
 */
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

/**
 * Get the name of the object.
 *
 * @return the name of the object
 *
 */
std::string Object::getName() const {
    return name;
}

/**
 * Get the position of the Object.
 *
 * @return the position of the Object as a vector of doubles
 */
std::vector<double> Object::getPosition() const {
    return position;
}

/**
 * Get the speed of the Object.
 *
 * @return a vector of doubles representing the speed
 */
std::vector<double> Object::getSpeed() const {
    return speed;
}

std::vector<double> Object::getAcceleration() const {
    return acceleration;
}

/**
 * Get the mass of the object.
 *
 * @return the mass of the object
 */
double Object::getMass() const {
    return mass;
}

/**
 * Sets the name of the object.
 *
 * @param n the new name to set
 *
 * @return void
 *
 * @throws none
 */
void Object::setName(const std::string& n) {
    name = n;
}

/**
 * Set the position of the Object.
 *
 * @param pos vector of doubles representing the new position
 */
void Object::setPosition(std::vector<double>& pos) {
    position = pos;
}

/**
 * Sets the speed of the object.
 *
 * @param spd vector containing the speed values to set
 *
 * @return void
 *
 * @throws None
 */
void Object::setSpeed(std::vector<double>& spd) {
    speed = spd;
}

/**
 * Set the acceleration vector for the Object.
 *
 * @param acc The acceleration vector to set
 */
void Object::setAcceleration(std::vector<double>& acc) {
    acceleration = acc;
} 

/**
 * Set the mass of the object.
 *
 * @param m the mass to set
 *
 */
void Object::setMass(double m) {
    mass = m;
}

/**
 * Calculate gravitational force between two objects.
 *
 * @param obj The other object
 *
 * @return The gravitational force vector
 *
 * @throws None
 */
std::vector<double> Object::gravForce(const Object& obj) {
    std::vector<double> distVect = distanceVect(obj);
    std::vector<double> force(3);
    force[0] -= 6.67408E-11 * mass * obj.getMass() * distVect[0] / pow(distance(obj), 3);
    force[1] -= 6.67408E-11 * mass * obj.getMass() * distVect[1] / pow(distance(obj), 3);
    force[2] -= 6.67408E-11 * mass * obj.getMass() * distVect[2] / pow(distance(obj), 3);
    return force;
}

/**
 * Compute the acceleration of the object based on the gravitational force from other objects.
 *
 * @param objects the vector of other Object instances
 *
 * @return void
 *
 * @throws ErrorType (if applicable) description of error
 */
void Object::computeAcceleration(std::vector<Object>& objects) {
    std::vector<double> accel(3);
    for(Object obj : objects) {
        for (int l = 0; l<=2; l++) {
            accel[l] += gravForce(obj)[l] / mass;
        }
    }
    setAcceleration(accel);
}

/**
 * Generates a vector representing the distance between the current object and the passed object.
 *
 * @param obj The object to calculate the distance from.
 *
 * @return A vector containing the distances in each dimension.
 *
 * @throws None
 */
std::vector<double> Object::distanceVect(Object obj) {
    std::vector<double> objPosition = obj.getPosition();
    std::vector<double> distanceVect;
    distanceVect.push_back(position[0] - objPosition[0]);
    distanceVect.push_back(position[1] - objPosition[1]);
    distanceVect.push_back(position[2] - objPosition[2]);
    return distanceVect;
}
/**
 * Calculates the distance between this Object and the input Object.
 *
 * @param obj The Object to calculate the distance to.
 *
 * @return The Euclidean distance between the two Objects.
 *
 * @throws None
 */
double Object::distance(const Object& obj){
    std::vector<double> objPosition = obj.getPosition();
    return(sqrt(pow(position[0]-objPosition[0],2)+
            pow(position[1]-objPosition[1],2)+
            pow(position[2]-objPosition[2],2)));
}

/**
 * Calculate the kinetic energy of the object.
 *
 * @return the calculated kinetic energy
 */
double Object::kineticEnergy() {
    double kinetic = 0.5 * mass * (speed[0] * speed[0] + speed[1] * speed[1] + speed[2] * speed[2]);
    return kinetic;
}

/**
 * Compute the potential energy of the objects in the given vector.
 *
 * @param objects vector of Object instances for which potential energy needs to be computed
 *
 * @return void
 *
 * @throws N/A
 */
void Object::computePotentialEnergy(std::vector<Object>& objects) {
    double potential;
    for (Object obj : objects) {
        potentialEnergy +=sqrt(gravForce(obj)[0] * gravForce(obj)[0] +
                            gravForce(obj)[1] * gravForce(obj)[1] +
                            gravForce(obj)[2] * gravForce(obj)[2])*mass*
                            distance(obj);
    }
}

/**
 * Clear the potential energy of the object.
 */
void Object::clearPotentialEnergy() {
    potentialEnergy = 0;
}

/**
 * Calculates the total energy by summing the kinetic and potential energy.
 *
 * @return the total energy as a double
 */
double Object::totalEnergy() {
    double total = kineticEnergy() + potentialEnergy;
    return total;
}


