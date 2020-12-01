#include <iostream>
#include <vector>
#include "vektor.h"
using namespace std;
int norma(const Vektor & vec)
{
    int suma=0;
    for(int i=0;i<vec.data.size();i++)
    {
      suma+=abs(vec.data[i]);
    }
    return suma;
}
Vektor::Vektor(const Vektor & vec){
  data.resize(vec.data.size());
  for (int i = 0; i < data.size(); i++)
  {
    data[i]=vec.data[i];
  }  
}
Vektor& Vektor::operator|(int a)
{
  data.push_back(a);
  return *this;
}
Vektor& operator|(int a,Vektor& vec)
	{
    vec.data.resize(vec.data.size()+1);
    for (int i = vec.data.size()-1; i >=1; i--)
    {
      vec.data[i]=vec.data[i-1];
    }
    vec.data[0]=a;
    return vec;
	}
int Vektor::operator[](int index) const{
  if(data.size()==1)return data[0];
  int a=index;
  while(a>=data.size())
  {
    a-=data.size();
  }
  while(a<0)
  {
    a+=data.size();
  }
  return data[a];
}
int & Vektor::operator[](int index){
  if(data.size()==1)return data[0];
  while(index>=data.size())
  {
    index-=data.size();
  }
  while(index<0)
  {
    index+=data.size();
  }
  return data[index];
}
int Vektor::operator*(const Vektor& vec1)
  {
    if(vec1.data.size()==0||data.size()==0||vec1.data.size()!=data.size())
      return 0;
    else
    {
      int suma=0;
      for(int i=0;i<vec1.data.size();i++)suma+=vec1.data[i]*data[i];
      return suma;
    }
    return 0;
  }
	std::ostream & operator<<(std::ostream & out, const Vektor& vec) {
		out << "(";
		for (int i = 0; i<vec.data.size(); i++)
		{
			if (i<vec.data.size() - 1)
				out << vec.data[i] << ",";
			else
				out << vec.data[i];
		}
		out << ")";
		return out;
	}
Vektor Vektor::operator%(int x)
{
    Vektor novi;
    if(x<0)return novi;
    Vektor n;
    for(int i=0;i<data.size();i++){
      n.data.clear();
      int nor=0;
      for(int j=i;j<data.size();j++)
      { 
        if(abs(data[j])>x-nor)break;       
        n.data.push_back(data[j]);
        nor+=abs(data[j]);
        if(nor==x)return n;
      }
    }
    return novi;
}
Vektor& Vektor::operator--()
{
  if(data.size()>0){
    data.erase(data.begin());
  }
  return *this;
}
Vektor Vektor::operator--(int)
{
  if(data.size()>0){
    data.pop_back();
  }
  return *this;
}
int Vektor::operator+()
{
  if(data.size()==0)return 0;
  int max=0;
  for (int i = 0; i < data.size(); i++)
  {
    if(abs(data[i])>max)
      max=abs(data[i]);
  }
  return max;
}
int Vektor::operator-()
{
  if(data.size()==0)return 0;
  int min=INT32_MAX;
  for (int i = 0; i < data.size(); i++)
  {
    if(abs(data[i])<min)
      min=abs(data[i]);
  }
  return min;
}
Vektor Vektor::operator&(const Vektor& vec){
  Vektor novi;
      novi.data.resize(vec.data.size()+data.size());
      for(int i=0;i<data.size();i++)
        novi.data[i]=data[i];
      for(int i=0;i<vec.data.size();i++)
        novi.data[data.size()+i]=vec.data[i];
      return novi;  
}

