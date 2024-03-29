#include "util.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

double RK4(double x,double v,double a,double h,double force,double m)
{
//Pour la position  x(t)=v(t)*t+x_0 -> v(t,x)=x(t)/t-x_0/t
//Pour la vitesse   v(t)=a(t)*t+v_0
//Pour l'acélération a(t)=F/m

//k1=f(t_n,y_n)
double k1x=v;
double k1v=force/m;
//k2=f(t_n+h/2,y_n+h/2*k1)
double k2x=v+(h/2)*k1x;
double k2v=force/m+(h/2)*k1v;
//k3=f(t_n+h/2,y_n+h/2*k2)
double k3x=v+(h/2)*k2x;
double k3v=force/m+(h/2)*k2v;
//k4=f(t_n+h,y_n+h*k3)
double k4x=v+h*k3x;
double k4v=force/m+h*k3v;

x+=(h/6)*(k1x+2*k2x+2*k3x+k4x);
v+=(h/6)*(k1v+2*k2v+2*k3v+k4v);

return v;

}


//norme
double norme(vector<double>& vect)
{
return sqrt(vect[0]*vect[0]+vect[1]*vect[1]+vect[2]*vect[2]) ;
}

