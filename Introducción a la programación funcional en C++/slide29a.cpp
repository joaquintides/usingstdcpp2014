#include <cmath>
#include <functional>
#include <iostream>

using namespace std;
using namespace std::placeholders;

typedef function<double(double)> real_function;

double derivative_at(real_function f,double x)
{
  static const double h=1.0E-5;
  return (f(x+h)-f(x-h))/(2*h);
}

real_function derivative(real_function f)
{
  return bind(derivative_at,f,_1);
}

int main()
{
  real_function s=(double(*)(double))&sin; // ugly as sin
  real_function ms=[](double x){return -sin(x);};
  real_function dds=derivative(derivative(s));
  
  cout<<"exact\t\tcalculated\n";
  for(double x=0.;x<3.14159265;x+=0.05){
    cout<<ms(x)<<"\t"<<dds(x)<<"\n";
  }
}
