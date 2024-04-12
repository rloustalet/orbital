#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

using namespace std;

class Object {
    private:
        string name;
        vector<double> position;
        vector<double> speed;
        vector<double> acceleration;
        vector<double> force;
        double mass;
        double potentialEnergy;
        double area;


    public:
        Object(const string& n, vector<double>& pos, vector<double>& spd,
        vector<double>& acc, double m);

        string getName() const;
        vector<double> getPosition() const;
        vector<double> getSpeed() const;
        vector<double> getAcceleration() const;
        double getMass() const;
        double getArea() const;

        void setName(const string& n);
        void setPosition(vector<double>& pos);
        void setSpeed(vector<double>& spd);
        void setAcceleration(vector<double>& acc);
        void setMass(double m);

        void computeAcceleration(vector<Object>& objects);
        vector<double> distanceVect(Object obj);
        double distance(const Object& obj);
        vector<double> gravForce(const Object& obj);
        double kineticEnergy();
        void computePotentialEnergy(vector<Object>& objects);
        double totalEnergy();
        void clearPotentialEnergy();
        double normeCinematicMoment();
        void computeArea(double h);

    
};

#endif