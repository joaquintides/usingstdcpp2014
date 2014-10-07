#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stack>

using namespace std;
using namespace placeholders;

class document
{
public:
  typedef vector<string>               data;
  typedef function<void(data&)>        undo_action;
  typedef function<undo_action(data&)> command;
  typedef function<void(data&)>        default_undo_command;

  document(const data& dat):dat(dat){}
  
  void do_(const command& f)
  {
    undo_stack.push(f(dat));
  }
  
  void do_default_undo(const default_undo_command& f)
  {
    auto undo_f=bind(&data::swap,_1,dat);
    f(dat);
    undo_stack.push(move(undo_f));
  }

  bool undo()
  {
    if(undo_stack.empty())return false;
    undo_stack.top()(dat);
    undo_stack.pop();
    return true;
  }
  
  friend ostream& operator<<(ostream& os,const document& doc)
  {
    for(const auto& word:doc.dat)os<<word<<" ";
    return os<<"\n";
  }

private:
  data               dat;
  stack<undo_action> undo_stack;
};

void reverse(document& doc)
{
  doc.do_([](document::data& dat)
  {
    reverse(dat.begin(),dat.end());
    
    return [](document::data& dat)
    {
      reverse(dat.begin(),dat.end());
    };
  });
}

void append(document& doc,const string& word)
{
  doc.do_([word](document::data& dat)
  {
    dat.push_back(word);
    
    return [](document::data& dat)
    {
      dat.pop_back();
    };
  });
}

void insert(document& doc,size_t pos,const string& word)
{
  doc.do_([pos,word](document::data& dat)
  {
    dat.insert(dat.begin()+pos,word);
    
    return [pos](document::data& dat)
    {
      dat.erase(dat.begin()+pos);
    };
  });
}

void erase(document& doc,size_t pos)
{
  doc.do_([pos](document::data& dat)
  {
    string word=dat[pos];
    dat.erase(dat.begin()+pos);
    
    return [pos,word](document::data& dat)
    {
      dat.insert(dat.begin()+pos,word);
    };
  });
}

void clear(document& doc)
{
  doc.do_default_undo([](document::data& dat)
  {
    dat.clear();
  });
}

void sort(document& doc)
{
  doc.do_default_undo([](document::data& dat)
  {
    sort(dat.begin(),dat.end());
  });
}

int main()
{
  document doc=document::data{"hola","cómo","están","hoy"};
  cout<<"start:\t"<<doc;
  
  append(doc,"martes");
  cout<<"append:\t"<<doc;
  
  insert(doc,3,"ustedes");
  cout<<"insert:\t"<<doc;
  
  erase(doc,0);
  cout<<"erase:\t"<<doc;

  sort(doc);
  cout<<"sort:\t"<<doc;

  reverse(doc);
  cout<<"revers:\t"<<doc;

  clear(doc);
  cout<<"clear:\t"<<doc;

  cout<<"undoing...\n";
  
  while(doc.undo())cout<<"undo:\t"<<doc;
}
