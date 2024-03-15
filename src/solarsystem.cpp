#include <vector>
#include <cmath>
#include <iostream>
#include "solarsystem.h"
#include "util.h"


using namespace std;
SolarSystem::SolarSystem(const string& n,const vector<Object>& objects): name(n), objects(objects) {
    this->name=n;
    this->objects=objects;
}

void SolarSystem::solve(double h,double t){
    //donne la positon de la terre et du soleil à t
    double steps=t/h;
    double v;
    double x;
    double a;
    double force;
    double m;

    vector<double>position;
    vector<double>vitesse;
    vector<double>acceleration;

    for(int i=0;i<=steps;i++)
    {
        for(int j=0;j<=2;j++)
        {
        //Verlet(double x,double v,double a,double h,double force,double m )
        x=objects[1].getPosition()[j];
        v=objects[1].getSpeed()[j];
        a=objects[1].getAcceleration()[j];
        force=objects[1].gravForce(objects[0]);
        m=objects[1].getMass();

        vitesse[j]=Verlet(x,v,a,h,force,m);
        cout<<"vitesse ="<<vitesse[j]<<endl;
        position[j]=vitesse[j]*h*i;
        cout<<"position ="<<position[j]<<endl;
        }
        objects[1].setPosition(position);
        objects[1].setSpeed(vitesse);

    }
}

