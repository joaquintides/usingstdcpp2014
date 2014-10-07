#include <cstdio>
#include <functional>
#include <iostream>
#include <utility>
#include <string>

template<typename T,typename R>
using func=std::function<R(T)>;

template<typename T,typename R>
struct yarn:func<func<T,R>,R>
{
  using value_type=T;
  using result_type=R;
  using super=func<func<T,R>,R>;
  using super::super;
  yarn(const T& x):
    super([x](const func<T,R>& f){return f(x);}){}

  template<typename F>
  auto then(F f)const
  {
    using T2=decltype(f(std::declval<T>()));
    return *this>>=
      [f](const T& x)->yarn<T2,R>{return f(x);};
  }
  
  R run(){return (*this)([](const T& x){return R(x);});}
};

template<typename T,typename R,typename F>
auto operator>>=(const yarn<T,R>& c,F f)
{
  using T2=typename decltype(f(std::declval<T>()))::value_type;
  
  return yarn<T2,R>(
    [c,f](const func<T2,R>& k){
      return c([f,k](const T& t){
        return f(t)(k);
      });
    }
  );
}

int str_size(const std::string& str)
{
  std::cout<<"str_size(\""<<str<<"\")\n";
  return str.size();
}

int times_10(int x)
{
  std::cout<<"times_10("<<x<<")\n";
  return 10*x;
}

std::string to_str(int x)
{
  std::cout<<"to_str("<<x<<")\n";
  char buf[128];
  sprintf(buf,"%d",x);
  return buf;
}

int main()
{
  auto c1=yarn<std::string,int>("hello").
    then(str_size).
    then(times_10).
    then(to_str).
    then(str_size);
    
  std::cout<<"running...\n";
  std::cout<<c1.run()<<"\n";
}
