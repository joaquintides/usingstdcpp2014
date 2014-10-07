#include <functional>
#include <iostream>
#include <string>

void f(const std::string& s0,const std::string& s1,const std::string& s2)
{
  std::cout<<"From "<<s0<<" to "<<s1<<" through "<<s2<<"\n";
}

using namespace std::placeholders;

int main()
{
  auto f1=std::bind(f,"New York",_1,_2); // what’s the return type?
  auto f2=std::bind(f,"Moscow","Beijing",_1);
  auto f3=std::bind(f,_2,_1,_3);

  f1("Los Angeles","Denver");
  f2("Ulan Bator");
  f3("Madrid","Paris","Barcelona");
}
