#include <boost/optional.hpp>
#include <iostream>
#include <cmath>

template<typename T>
std::ostream& operator<<(std::ostream& os,const boost::optional<T>& x)
{
  if(x)return os<<x.get();
  else return os<<"none";
}

using namespace boost;

optional<double> inv(double x)
{
  if(x==0.0)return none;
  else      return 1.0/x;
}

optional<double> sqr(double x)
{
  if(x<0.0)return none;
  else     return std::sqrt(x);
}

optional<double> arcsin(double x)
{
  if(x<-1.0||x>1.0)return none;
  else             return std::asin(x);
}

optional<double> f(double x)
{
  auto y=sqr(x);
  auto z=y?arcsin(y.get()):none;
  auto w=z?inv(z.get()):none;
  
  return w;
}

int main()
{
  std::cout<<"f(1.0)="<<f(1.0)<<"\n";
  std::cout<<"f(-1.0)="<<f(-1.0)<<"\n";
  std::cout<<"f(2.0)="<<f(-1.0)<<"\n";
  std::cout<<"f(0.0)="<<f(-1.0)<<"\n";
}
