#include <iostream>
#include <vector>

using namespace std;
#include "../src/util.h"
int main()
{
//on trouve pour ces valeurs x=1.47098E+11 
double x;
double v;
double a;
//double RK4(double x,double v,double a,double h,double force,double m)
x=RK4(147098290E3,0,9025486703,3600,-5.391464737E34,5.9736E24);
cout<<"v= "<<x<<endl;
//double Verlet(double x,double v,double a,double h,double force,double m )
x=Verlet(147098290E3,0,9025486703,3600,-5.391464737E34,5.9736E24 );
cout<<"v = "<<x<<endl;



//double norme(vector<double>& vect)
vector<double>T;
T.push_back(1);
T.push_back(2);
T.push_back(3);

cout<<"norme= "<<norme(T)<<endl;
}