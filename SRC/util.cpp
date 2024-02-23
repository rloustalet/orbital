
using namespace std;

double RK4(double x,double v,double a,double h,double force,double m,double t )
{
//Pour la position  x(t)=v(t)*t+x_0 -> v(t,x)=x(t)/t-x_0/t
//Pour la vitesse   v(t)=a(t)*t+v_0
//Pour l'acélération a(t)=F/m

//k1=f(t_n,y_n)
double k1x=v
double k1v=F/m
//k2=f(t_n+h/2,y_n+h/2*k1)
double k2x=v+(h/2)*k1x
double k2v=F/m+(h/2)*k1v
//k3=f(t_n+h/2,y_n+h/2*k2)
double k3x=v+(h/2)*k2x
double k3v=F/m+(h/2)*k2v
//k4=f(t_n+h,y_n+h*k3)
double k4x=v+h*k3x
double k4v=F/m+h*k3v

x+=(h/6)*(k1x+2*k2x+2*k3x+k4x)
v+=(h/6)*(k1v+2*k2v+2*k3v+k4v)

return x

}

double Verlet(double x,double v,double a,double h,double force,double m )
{
//x(t+h)=x(t)+v(t)*h+1/2*a(t)*h**2
//v(t+h/2)=v(t)+a(t)*h/2
//a(t+h)=
//v(t+h)=v(t+h/2)+a(t+h)*h/2
x+=v*h+(1/2)*a*(h**2)
v+=a*(h/2)
a+=froce/m
v=v+(a*h)/2

return x
}

