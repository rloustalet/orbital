#include <vector>

double RK4(double x,double v,double a,double h,double force,double m);
double Verlet(double x,double v,double a,double h,double force,double m );
double norme(std::vector<double>& vect);