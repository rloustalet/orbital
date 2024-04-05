#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

class Object {
    private:
        std::string name;
        std::vector<double> position;
        std::vector<double> speed;
        std::vector<double> acceleration;
        std::vector<double> force;
        double mass;
        double potentialEnergy;


    public:
        Object(const std::string& n, std::vector<double>& pos, std::vector<double>& spd,
        std::vector<double>& acc, double m);

        std::string getName() const;
        std::vector<double> getPosition() const;
        std::vector<double> getSpeed() const;
        std::vector<double> getAcceleration() const;
        double getMass() const;

        void setName(const std::string& n);
        void setPosition(std::vector<double>& pos);
        void setSpeed(std::vector<double>& spd);
        void setAcceleration(std::vector<double>& acc);
        void setMass(double m);

        void computeAcceleration(std::vector<Object>& objects);
        std::vector<double> distanceVect(Object obj);
        double distance(const Object& obj);
        std::vector<double> gravForce(const Object& obj);
        double kineticEnergy();
        void computePotentialEnergy(std::vector<Object>& objects);
        double totalEnergy();
        void clearPotentialEnergy();

    
};

#endif