#include <cmath>
#include <iostream>

using namespace std;

template<typename F>
double derivative_at(F f,double x)
{
  static const double h=1.0E-5;
  return (f(x+h)-f(x-h))/(2*h);
}

template<typename F>
auto derivative(F f)
{
  return [=](double x){return derivative_at(f,x);};
}

int main()
{
  auto s=(double(*)(double))&sin; // ugly as sin
  auto ms=[](double x){return -sin(x);};
  auto dds=derivative(derivative(s));
  
  cout<<"exact\t\tcalculated\n";
  for(double x=0.;x<3.14159265;x+=0.05){
    cout<<ms(x)<<"\t"<<dds(x)<<"\n";
  }
}
