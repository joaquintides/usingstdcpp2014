#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#if 0
template<typename Container>
void abs_sort(Container& c)
{
  typedef typename Container::value_type value_type;
  std::sort(
    c.begin(),c.end(),
    [](const value_type& x,const value_type& y)
    {return abs(x)<abs(y);});
}
#endif

template<typename Container>
void abs_sort(Container& c)
{
  std::sort(
    c.begin(),c.end(),
    [](const auto& x,const auto& y){return abs(x)<abs(y);});
}

int main()
{

vector<int> v={0,2,-2,-10,1,-5};
abs_sort(v);
}
