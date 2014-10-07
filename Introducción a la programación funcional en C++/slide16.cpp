#include <functional>
#include <iostream>
#include <string>

struct eval
{
  template<typename F>
  void operator()(F f, int x)const{
    std::cout<<"f("<<x<<")="<<f(x)<<"\n";
  }
};

int foo(int x,int y){return x+y;}

using namespace std::placeholders;

int main()
{
  auto f=std::bind(foo,5,_1);
  auto g=std::bind(eval(),f,_1); // bind(eval(),bind(foo,5,_1),_1)
  
  eval()(f,2); // "f(2)=7"
  g(2);        // ??
}
