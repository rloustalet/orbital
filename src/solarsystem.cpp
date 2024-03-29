#include <vector>
#include <cmath>
#include <iostream>
#include "solarsystem.h"
#include "util.h"
#include <fstream>


using namespace std;
SolarSystem::SolarSystem(const std::string& n,const vector<Object>& objs): name(n), objects(objs) {
    this->name=n;
    this->objects=objs;
}

void SolarSystem::solve(string algo, double h,double t){
    //donne la positon de la terre et du soleil à t
    for (Object obj : objects) {
        string name = obj.getName() + ".csv";
        if (std::remove(name.c_str()) != 0) {
        std::cout << "Le fichier n'existe pas ou n'a pas pu être supprimé." << std::endl;
    } else {
        std::cout << "Le fichier a été supprimé avec succès." << std::endl;
    }
    }

    double steps=t/h;

    for(int i=0;i<=steps;i++)
    {
        for (int j=0;j<objects.size();j++) {
            vector<Object> subobjects = objects;
            subobjects.erase(subobjects.begin() + j);
            for (Object obj2 : subobjects) {
                if (algo == "RK4") {
                    RK4(objects[j], obj2, h);
                }
                else if (algo == "verlet") {
                    verlet(objects[j], obj2, h);
                }
                else{
                    std::cout << "l'algorithme n'existe pas" << std::endl;
                }
                
            }
            exportdata(objects[j]);
        }

    }
}

void SolarSystem::exportdata(Object obj){
    std::ofstream outfile;
    string name = obj.getName() + ".csv";
    outfile.open(name, std::ios_base::app);
    outfile << obj.getName() << " " << obj.getPosition()[0] << " " 
    << obj.getPosition()[1] << " " << obj.getPosition()[2] << std::endl;
    outfile.close();
}

void SolarSystem::verlet(Object &obj1,Object obj2, double h)
{
//x(t+h)=x(t)+v(t)*h+1/2*a(t)*h**2
//v(t+h/2)=v(t)+a(t)*h/2
//a(t+h)=
//v(t+h)=v(t+h/2)+a(t+h)*h/2
vector<double>position = obj1.getPosition();
vector<double>vitesse = obj1.getSpeed();
vector<double>acceleration = obj1.getAcceleration();

for(int j=0;j<=2;j++)
        {
        position[j] += vitesse[j]*h+(1/2)*obj1.getAcceleration()[j]*(h*h);
        }
obj1.setPosition(position);
std::vector<double>force = obj1.gravForce(obj2);
for(int j=0;j<=2;j++)
        {
        vitesse[j] += (obj1.getAcceleration()[j] + force[j]/obj1.getMass())*h/2;
        acceleration[j] = (force[j]/obj1.getMass());
        }
obj1.setSpeed(vitesse);
obj1.setAcceleration(acceleration);

cout << obj1.getName() << endl;
cout << "distance << " << obj1.distance(obj2) << endl;
cout << "force << " << force[0] << " " << force[1] << " " << force[2] << endl;
cout << "acceleration << " << force[0]/obj1.getMass() << " " << force[1]/obj1.getMass() << " " << force[2]/obj1.getMass() << endl;
cout << "norme force << " << sqrt(force[0]*force[0]+force[1]*force[1]+force[2]*force[2]) << endl;
}

void SolarSystem::RK4(Object &obj1, Object obj2, double h)
{
std::vector<double>positioninit = obj1.getPosition();
std::vector<double>position1 = obj1.getPosition();
std::vector<double>position2 = obj1.getPosition();
std::vector<double>position3 = obj1.getPosition();
std::vector<double>vitesseinit = obj1.getSpeed();
std::vector<double>vitesse = obj1.getSpeed();
std::vector<double>acceleration = obj1.getAcceleration();

std::vector<double>force = obj1.gravForce(obj2);

double k0 = h*force[0]/obj1.getMass();
double l0 = h*force[1]/obj1.getMass();

position1[0] += 0.5*k0*h;
position1[1] += 0.5*l0*h;
obj1.setPosition(position1);

std::vector<double>force2 = obj1.gravForce(obj2);
double k1 = 0.5*h*force2[0]/obj1.getMass();
double l1 = 0.5*h*force2[1]/obj1.getMass();

position2[0] += 0.5*k1*h;
position2[1] += 0.5*l1*h;
obj1.setPosition(position2);

std::vector<double>force3 = obj1.gravForce(obj2);
double k2 = 0.5*h*force3[0]/obj1.getMass();
double l2 = 0.5*h*force3[1]/obj1.getMass();

position3[0] += k2*h;
position3[1] += l2*h;
obj1.setPosition(position3);

std::vector<double>force4 = obj1.gravForce(obj2);
double k3 = h*force4[0]/obj1.getMass();
double l3 = h*force4[1]/obj1.getMass();

vitesse[0] = (k0 + 2*k1 + 2*k2 + k3)/6;
vitesse[1] = (l0 + 2*l1 + 2*l2 + l3)/6;
obj1.setSpeed(vitesse);

acceleration[0] = vitesse[0]/h;
acceleration[1] = vitesse[1]/h;
obj1.setAcceleration(acceleration);

positioninit[0] += vitesseinit[0]*h;
positioninit[1] += vitesseinit[1]*h;
obj1.setPosition(positioninit);
}

