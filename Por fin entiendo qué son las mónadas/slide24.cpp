#include <boost/optional.hpp>
#include <map>
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& os,const boost::optional<T>& x)
{
  if(x)return os<<x.get();
  else return os<<"none";
}

using namespace boost;

template<typename T,typename F>
auto operator>>=(const optional<T>& x,F&& f)
{
  return x?f(x.get()):none;
}

template<typename T>
class histogram
{
  using impl_t=std::map<T,double>;
  
public:
  histogram(){}
  histogram(const T& x){m[x]=1.0;}
  
  using const_iterator=typename impl_t::const_iterator;
  
  const_iterator begin()const{return m.begin();}
  const_iterator end()const{return m.end();}
  
  void add(const T& x,double f){m[x]+=f;}
    
private:
  impl_t  m;
};

template<typename T>
std::ostream& operator<<(std::ostream& os,const histogram<T>& h)
{
  for(const auto& p:h){
    os<<p.first<<"\t";
    for(int n=p.second*120;n--;)os<<"*";
    os<<"\n";
  }
  return os;
}

template<typename T,typename F>
auto operator>>=(const histogram<T>& x,F&& f)
{
  decltype(f(x.begin()->first)) res;
  
  for(const auto& p:x){
    for(const auto& q:f(p.first)){
      res.add(q.first,q.second*p.second);
    }
  }

  return res;
}

histogram<int> dice(int n)
{
  histogram<int> res;
  for(int i=1;i<=n;++i)res.add(i,1.0/n);
  return res;
}

template<template<typename> class M,typename T1,typename T2>
auto operator+(const M<T1>& m1,const M<T2>& m2)
{
  return m1>>=[&](const T1& x){
    return m2>>=[&](const T2& y){
      return M<decltype(x+y)>(x+y);
    };
  };
}

int main()
{
  auto h1=dice(6);
  auto h2=dice(4);
  auto h3=h1+h2;
  
  std::cout<<h3;
  std::cout<<"--------------------------\n";
  std::cout<<optional<int>(4)+optional<int>(3)<<"\n";
  std::cout<<optional<int>(4)+optional<int>(none)<<"\n";
}
