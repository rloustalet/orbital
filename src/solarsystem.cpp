#include <vector>
#include <cmath>
#include <iostream>
#include "solarsystem.h"
#include "util.h"
#include <fstream>


using namespace std;
SolarSystem::SolarSystem(const std::string& n,const vector<Object>& objs): name(n), objects(objs) {
    this->name=n;
    this->objects=objects;
}

void SolarSystem::solve(double h,double t){
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
                verlet(objects[j], obj2, h);
            }
            cout<<"special" << objects[j].getName() << " " << objects[j].getPosition()[0] << " " << objects[j].getPosition()[1] << endl;
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
double distance = obj1.distance(obj2);
double cos_theta = (obj1.getPosition()[0]- obj2.getPosition()[0]) / distance;
double sin_theta = (obj1.getPosition()[1]- obj2.getPosition()[1]) / distance;
double force = obj1.gravForce(obj2);
cout << "force" << force << std::endl;
cout << "cos" << cos_theta << std::endl;
cout << "sin" << sin_theta << std::endl;
cout << "distance" << distance << std::endl;
acceleration[0] = (force/obj1.getMass()) * cos_theta;
acceleration[1] = (force/obj1.getMass()) * sin_theta;
for(int j=0;j<=1;j++)
        {
        position[j] += vitesse[j]*h+(1/2)*obj1.getAcceleration()[j]*(h*h);
        vitesse[j] += (obj1.getAcceleration()[j] + acceleration[j])*h/2;
        }
cout << obj1.getName() << endl;
obj1.setPosition(position);
obj1.setSpeed(vitesse);
obj1.setAcceleration(acceleration);
cout << "speed" << obj1.getSpeed()[0] << " " <<  obj1.getSpeed()[1] << " " << obj1.getSpeed()[2] << std::endl;
cout << "distance" << obj1.getPosition()[0] << " " << obj1.getPosition()[1] << std::endl;
}