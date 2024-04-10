#include "planet.h"
#include <cmath>
#include "object.h"


using namespace std;

Planet::Planet(const std::string& n, std::vector<double>& pos, std::vector<double>& spd,
std::vector<double>& acc, double m) : Object(n, pos, spd, acc, m) {}


double Planet::normeCinematicMoment(Star star)
{
   vector<double> distance=distanceVec(star);
   vector<double> vitesse=getSpeed();

   double dx = distance[0];
   double dy = distance[1];
   double dz = distance[2];
   double vx = vitesse[0];
   double vy = vitesse[1];
   double vz = vitesse[2];   
   double normeL;
   return normeL= getMass() * sqrt((dy*vz-dz*vy)*(dy*vz-dz*vy)+(dz*vx-dx*vz)*(dz*vx-dx*vz)+(dx*vy-dy*vx)*(dx*vy-dy*vx));
}

double Planet::area(Star star,double t) 
{
   double area = 0.5 * t *sqrt(normeCinematicMoment(star))/getMass();
   return area;
}







