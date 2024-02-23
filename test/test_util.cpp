#include <iostream>

using namespace std;
#include "../src/util.h"
int main()
{

double x;
double v;
double a;
x=RK4(147098290E3,0,9025486703,3600,-5.391464737E34,5.9736E24,0);
cout<<"x = "<<x<<endl;
//cout<<"v = "<<x<<endl;
x=Verlet(147098290E3,0,9025486703,3600,-5.391464737E34,5.9736E24 );
cout<<"x = "<<x<<endl;
//cout<<"v = "<<x<<endl;
//cout<<"a = "<<x<<endl;
}
