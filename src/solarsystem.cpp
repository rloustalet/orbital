#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <functional>
#include "solarsystem.h"
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

    transform(algo.begin(), algo.end(), algo.begin(), ::tolower);

    for(int i=0;i<=steps+1;i++)
    {
        for (int j=0;j<objects.size();j++) {
            vector<Object> subobjects = objects;
            subobjects.erase(subobjects.begin() + j);
            exportdata(objects[j]);
            std::cout << objects[j].getName() << std::endl;
            if (algo == "rk4") {
                RK4(objects[j], subobjects, h);
            }
            else if (algo == "verlet") {
                verlet(objects[j], subobjects, h);
            }
            else{
                std::cout << "l'algorithme n'existe pas" << std::endl;
            }
            objects[j].computePotentialEnergy(subobjects);
            objects[j].clearPotentialEnergy();

        }

    }
}

void SolarSystem::exportdata(Object obj){
    std::ofstream outfile;
    string name = obj.getName() + ".csv";
    outfile.open(name, std::ios_base::app);
    outfile << obj.getName() << " " << obj.getPosition()[0] << " " 
    << obj.getPosition()[1] << " " << obj.getPosition()[2] << " " 
    << obj.getSpeed()[0] << " " 
    << obj.getSpeed()[1] << " " << obj.getSpeed()[2] << " " << obj.totalEnergy() << std::endl;
    outfile.close();
}

void SolarSystem::verlet(Object &obj1, std::vector<Object> objects, double h)
{
//x(t+h)=x(t)+v(t)*h+1/2*a(t)*h**2
//v(t+h/2)=v(t)+a(t)*h/2
//a(t+h)=
//v(t+h)=v(t+h/2)+a(t+h)*h/2
vector<double>position = obj1.getPosition();
vector<double>vitesse = obj1.getSpeed();
vector<double> acceleration = obj1.getAcceleration();

for(int k=0;k<=2;k++)
        {
        position[k] += vitesse[k]*h+(1/2)*obj1.getAcceleration()[k]*(h*h);
        }
obj1.setPosition(position);
obj1.computeAcceleration(objects);
for(int k=0;k<=2;k++)
        {
        vitesse[k] += (acceleration[k] + obj1.getAcceleration()[k])*h/2;
        }
obj1.setSpeed(vitesse);

}

void SolarSystem::RK4(Object &obj1, std::vector<Object> objects, double h)
{
std::vector<double>position(3);
std::vector<double>positioninit = obj1.getPosition();
std::vector<double>vitesse = obj1.getSpeed();
std::vector<double>vitesseinit = obj1.getSpeed();
std::vector<double>force(3);

std::vector<double> k0(3);
std::vector<double> l0(3);

std::vector<double> k1(3);
std::vector<double> l1(3);

std::vector<double> k2(3);
std::vector<double> l2(3);

std::vector<double> k3(3);
std::vector<double> l3(3);

obj1.computeAcceleration(objects);

for (int k=0;k<=2;k++)
        {
        k0[k] = vitesse[k];
        l0[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k0);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + obj1.getSpeed()[k]*h/2;
        vitesse[k] = vitesseinit[k] + l0[k]*h/2;
        }

obj1.setPosition(position);

obj1.computeAcceleration(objects);

for(int k=0;k<=2;k++)
        {
        k1[k] = vitesse[k];
        l1[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k1);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + obj1.getSpeed()[k]*h/2;
        vitesse[k] = vitesseinit[k] + l1[k]*h/2;
        }

obj1.setPosition(position);

obj1.computeAcceleration(objects);

for(int k=0;k<=2;k++)
        {
        k2[k] = vitesse[k];
        l2[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k2);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + vitesse[k]*h;
        vitesse[k] = vitesseinit[k] + l2[k]*h;
        }

obj1.setPosition(position);

obj1.computeAcceleration(objects);

for(int k=0;k<=2;k++)
        {
        k3[k] =  vitesse[k];
        l3[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k3);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + (k0[k] + 2*k1[k] + 2*k2[k] + k3[k])*h/6;
        vitesse[k] = vitesseinit[k] + (l0[k] + 2*l1[k] + 2*l2[k] + l3[k])*h/6;
        }

obj1.setPosition(position);
obj1.setSpeed(vitesse);



}

bool SolarSystem::isStar(Object* obj) {
    return dynamic_cast<Object*>(obj) != nullptr;

}

