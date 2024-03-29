#include <vector>
#include <cmath>
#include <iostream>
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

    for(int i=0;i<=steps;i++)
    {
        for (int j=0;j<objects.size();j++) {
            vector<Object> subobjects = objects;
            subobjects.erase(subobjects.begin() + j);
            for (Object obj2 : subobjects) {
                std::cout << obj2.getName() << std::endl;
                if (algo == "RK4") {
                    RK4(objects[j], obj2, h);
                }
                else if (algo == "verlet") {
                    verlet(objects[j], obj2, h);
                }
                else{
                    std::cout << "l'algorithme n'existe pas" << std::endl;
                }
                objects[j].potentialEnergy(obj2);   
            }
            exportdata(objects[j]);
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
    << obj.getSpeed()[1] << " " << obj.getSpeed()[2] << obj.totalEnergy(obj) << std::endl;
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

for(int k=0;k<=2;k++)
        {
        position[k] += vitesse[k]*h+(1/2)*obj1.getAcceleration()[k]*(h*h);
        }
obj1.setPosition(position);
std::vector<double>force = obj1.gravForce(obj2);
for(int k=0;k<=2;k++)
        {
        vitesse[k] += (obj1.getAcceleration()[k] + force[k]/obj1.getMass())*h/2;
        acceleration[k] = (force[k]/obj1.getMass());
        }
obj1.setSpeed(vitesse);
obj1.setAcceleration(acceleration);

cout << obj1.getName() << endl;
cout << "distance << " << obj1.distance(obj2) << endl;
cout << "force << " << force[0] << " " << force[1] << " " << force[2] << endl;
cout << "acceleration << " << force[0]/obj1.getMass() << " " << force[1]/obj1.getMass() << " " << force[2]/obj1.getMass() << endl;
cout << "norme force << " << sqrt(force[0]*force[0]+force[1]*force[1]+force[2]*force[2]) << endl;
}

double SolarSystem::fonctionvitesse(double force,double t,double m,double vitesseinit)
{
    return t*force/m + vitesseinit ;
}

void SolarSystem::RK4(Object &obj1, Object obj2, double h)
{

std::vector<double>positioninit = obj1.getPosition();
std::vector<double>vitesse = obj1.getSpeed();
std::vector<double>acceleration = obj1.getAcceleration();

std::vector<double>force = obj1.gravForce(obj2);

double vx0 = fonctionvitesse(force[0],h,obj1.getMass(),vitesse[0]);
double vy0 = fonctionvitesse(force[1],h,obj1.getMass(),vitesse[1]);
double vz0 = fonctionvitesse(force[2],h,obj1.getMass(),vitesse[2]);

double vx1 = fonctionvitesse(force[0]+0.5*h*vx0,h+0.5*h,obj1.getMass(),vitesse[0]);
double vy1 = fonctionvitesse(force[1]+0.5*h*vy0,h+0.5*h,obj1.getMass(),vitesse[1]);
double vz1 = fonctionvitesse(force[2]+0.5*h*vz0,h+0.5*h,obj1.getMass(),vitesse[2]);

double vx2 = fonctionvitesse(force[0]+0.5*h*vx1,h+0.5*h,obj1.getMass(),vitesse[0]);
double vy2 = fonctionvitesse(force[1]+0.5*h*vy1,h+0.5*h,obj1.getMass(),vitesse[1]);
double vz2 = fonctionvitesse(force[2]+0.5*h*vz1,h+0.5*h,obj1.getMass(),vitesse[2]);

double vx3 = fonctionvitesse(force[0]+h*vx2,h+h,obj1.getMass(),vitesse[0]);
double vy3 = fonctionvitesse(force[1]+h*vy2,h+h,obj1.getMass(),vitesse[1]);
double vz3 = fonctionvitesse(force[2]+h*vz2,h+h,obj1.getMass(),vitesse[2]);


vitesse[0] = (vx0 + 2*vx1 + 2*vx2 + vx3)/6;
vitesse[1] = (vy0 + 2*vy1 + 2*vy2 + vy3)/6;
vitesse[2] = (vz0 + 2*vz1 + 2*vz2 + vz3)/6;
obj1.setSpeed(vitesse);

acceleration[0] = vitesse[0]/h;
acceleration[1] = vitesse[1]/h;
acceleration[2] = vitesse[2]/h;

acceleration[2] = vitesse[2]/h;

obj1.setAcceleration(acceleration);

positioninit[0] += h*vitesse[0];
positioninit[1] += h*vitesse[1];
positioninit[2] += h*vitesse[2];

obj1.setPosition(positioninit);

}

bool SolarSystem::isStar(Object* obj) {
    return dynamic_cast<Object*>(obj) != nullptr;

}

