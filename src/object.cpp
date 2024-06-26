#include "object.h"
#include <cmath>
#include <iostream>

using namespace std;

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
Object::Object(const string& n, vector<double>& pos, vector<double>& spd,
vector<double>& acc, double m) : name(n), position(pos),
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
string Object::getName() const {
    return name;
}

/**
 * Get the position of the Object.
 *
 * @return the position of the Object as a vector of doubles
 */
vector<double> Object::getPosition() const {
    return position;
}

/**
 * Get the speed of the Object.
 *
 * @return a vector of doubles representing the speed
 */
vector<double> Object::getSpeed() const {
    return speed;
}


/**
 * Get the acceleration of the Object.
 *
 * @return the acceleration of the Object as a vector of doubles
 */
vector<double> Object::getAcceleration() const {
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
 * Calculate and return the area of the object.
 *
 * @return the area of the object
 */
double Object::getArea() const{
   return area;
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
void Object::setName(const string& n) {
    name = n;
}

/**
 * Set the position of the Object.
 *
 * @param pos vector of doubles representing the new position
 */
void Object::setPosition(vector<double>& pos) {
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
void Object::setSpeed(vector<double>& spd) {
    speed = spd;
}

/**
 * Set the acceleration vector for the Object.
 *
 * @param acc The acceleration vector to set
 */
void Object::setAcceleration(vector<double>& acc) {
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
 * \f$ \overrightarrow{F}_{i\overrightarrow{}j} = 
 * - \frac{G m_{i}m_{j}}{{||\overrightarrow{r_{j}}-\overrightarrow{r_{i}}||}^3}
 * {(\overrightarrow{r_{j}}-\overrightarrow{r_{i}})} \f$
 *
 * @param obj The other object
 *
 * @return The gravitational force vector
 *
 * @throws None
 */
vector<double> Object::gravForce(const Object& obj) {
    vector<double> distVect = distanceVect(obj);
    vector<double> force(3);
    force[0] -= 6.67408E-11L * mass * obj.getMass() * distVect[0] / pow(distance(obj), 3);
    force[1] -= 6.67408E-11L * mass * obj.getMass() * distVect[1] / pow(distance(obj), 3);
    force[2] -= 6.67408E-11L * mass * obj.getMass() * distVect[2] / pow(distance(obj), 3);
    return force;
}

/**
 * Compute the acceleration of the object based on the gravitational force from other objects.
 * 
 * \f$ \overrightarrow{a}_{i} =\frac{\sum^{N}_{j=1,j \neq i}
 * \overrightarrow{F}_{i\overrightarrow{}{j}}}{m_{i}} \f$
 *
 * @param objects the vector of other Object instances
 *
 * @return void
 *
 * @throws ErrorType (if applicable) description of error
 */
void Object::computeAcceleration(vector<Object>& objects) {
    vector<double> accel(3);
    for(Object obj : objects) {
        vector<double> force = gravForce(obj);
        for (int l = 0; l<=2; l++) {
            accel[l] += force[l] / mass;
        }
    }
    setAcceleration(accel);
}

/**
 * Generates a vector representing the distance between the current object and the passed object.
 * 
 * \f$ \overrightarrow{r_{j}}-\overrightarrow{r_{i}} \f$
 *
 * @param obj The object to calculate the distance from.
 *
 * @return A vector containing the distances in each dimension.
 *
 * @throws None
 */
vector<double> Object::distanceVect(Object obj) {
    vector<double> objPosition = obj.getPosition();
    vector<double> distanceVect;
    distanceVect.push_back(position[0] - objPosition[0]);
    distanceVect.push_back(position[1] - objPosition[1]);
    distanceVect.push_back(position[2] - objPosition[2]);
    return distanceVect;
}
/**
 * Calculates the distance between this Object and the input Object.
 * 
 * \f$ ||\overrightarrow{r_{j}}-\overrightarrow{r_{i}}|| \f$
 *
 * @param obj The Object to calculate the distance to.
 *
 * @return The Euclidean distance between the two Objects.
 *
 * @throws None
 */
double Object::distance(const Object& obj){
    vector<double> objPosition = obj.getPosition();
    return(sqrt(pow(position[0]-objPosition[0],2)+
            pow(position[1]-objPosition[1],2)+
            pow(position[2]-objPosition[2],2)));
}

/**
 * Calculate the kinetic energy of the object.
 * 
 * \f$ E_{cinétique} ={\frac{1}{2}{m}}{\overrightarrow{v}^2} \f$
 *
 * @return the calculated kinetic energy
 */
double Object::kineticEnergy() {
    return 0.5 * mass * (pow(speed[0], 2) + pow(speed[1], 2) + pow(speed[2], 2));
}

/**
 * Compute the potential energy of the objects in the given vector.
 * 
 * \f$ E_{potentielle} ={||\overrightarrow{F}||}*{||\overrightarrow{r}||} \f$
 *
 * @param objects vector of Object instances for which potential energy needs to be computed
 *
 * @return void
 *
 * @throws N/A
 */
void Object::computePotentialEnergy(vector<Object>& objects) {
    double potential;
    for (Object obj : objects) {
        potentialEnergy += sqrt(pow(gravForce(obj)[0], 2) +
                            pow(gravForce(obj)[1], 2) +
                            pow(gravForce(obj)[2], 2))*
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


/**
 * Calculate the norm of the cinematic moment for the Object.
 * 
 * \f$ {\overrightarrow{L}= m*\overrightarrow{d}}\wedge{\overrightarrow{v}} \f$
 *
 * @return the norm of the cinematic moment
 */
double Object::normeCinematicMoment()
{
   vector<double> position = getPosition();
   vector<double> vitesse=getSpeed();

   double dx = position[0];
   double dy = position[1];
   double dz = position[2];
   double vx = vitesse[0];
   double vy = vitesse[1];
   double vz = vitesse[2];   
   return getMass() * sqrt(pow((dy*vz-dz*vy),2)+pow((dz*vx-dx*vz), 2)+pow((dx*vy-dy*vx), 2));
}

/**
 * Compute the area of the object based on the provided height.
 * 
 * \f$ Aire =\frac{1}{2}*\frac{||\overrightarrow{L}||}{m}*t \f$
 *
 * @param h the height of the object
 *
 * @return the computed area of the object
 *
 * @throws None
 */
void Object::computeArea(double h) 
{
   area = 0.5 * h *normeCinematicMoment()/getMass();
}
