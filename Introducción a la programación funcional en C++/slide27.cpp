#include <functional>
#include <iostream>
#include <string>

using namespace std::placeholders;

int f1(const std::string& s){return std::atoi(s.c_str());}
int f2(const std::string& s1,const std::string& s2){return f1(s1+s2);}

int main()
{
  std::function<int (const std::string&)> f=f1;
  std::cout<<f("123")<<std::endl;  // -> 123
  f=std::bind(f2,_1,"000");
  std::cout<<f("123")<<std::endl;  // -> 123000
  f=&std::string::size;            // wtf?
  std::cout<<f("123")<<std::endl;  // -> 3
}
