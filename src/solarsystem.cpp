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
    if (std::remove("data.txt") != 0) {
        std::cout << "Le fichier n'existe pas ou n'a pas pu être supprimé." << std::endl;
    } else {
        std::cout << "Le fichier a été supprimé avec succès." << std::endl;
    }

    double steps=t/h;

    for(int i=0;i<=steps;i++)
    {
        verlet(objects[1], h);

        exportdata();

    }
}

void SolarSystem::exportdata(){
    std::ofstream outfile;
    outfile.open("data.csv", std::ios_base::app);
    outfile << objects[1].getName() << " " << objects[1].getPosition()[0] << " " 
    << objects[1].getPosition()[1] << " " << objects[1].getPosition()[2] << std::endl;
    outfile.close();
}

void SolarSystem::verlet(Object obj, double h)
{
//x(t+h)=x(t)+v(t)*h+1/2*a(t)*h**2
//v(t+h/2)=v(t)+a(t)*h/2
//a(t+h)=
//v(t+h)=v(t+h/2)+a(t+h)*h/2
vector<double>position = objects[1].getPosition();
vector<double>vitesse = objects[1].getSpeed();
vector<double>acceleration = objects[1].getAcceleration();
double distance = obj.distance(objects[0]);
double cos_theta = (obj.getPosition()[0]- objects[0].getPosition()[0]) / distance;
double sin_theta = (obj.getPosition()[1]- objects[0].getPosition()[1]) / distance;
double force = obj.gravForce(objects[0]);
cout << "force" << force << std::endl;
cout << "cos" << cos_theta << std::endl;
cout << "sin" << sin_theta << std::endl;
cout << "distance" << distance << std::endl;
acceleration[0] = (force/obj.getMass()) * cos_theta;
acceleration[1] = (force/obj.getMass()) * sin_theta;
for(int j=0;j<=1;j++)
        {
        position[j] += vitesse[j]*h+(1/2)*obj.getAcceleration()[j]*(h*h);
        vitesse[j] += (obj.getAcceleration()[j] + acceleration[j])*h/2;
        }

objects[1].setPosition(position);
objects[1].setSpeed(vitesse);
objects[1].setAcceleration(acceleration);
cout << "speed" << objects[1].getSpeed()[0] << " " <<  objects[1].getSpeed()[1] << " " << objects[1].getSpeed()[2] << std::endl;
cout << "distance" << obj.distance(objects[0]) << std::endl;
}