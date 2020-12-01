#include <iostream>
#include <vector>
#include "vektor.h"
#include <cstdint>
#include <limits>
#include <math.h>
using namespace std;

Vektor::Vektor(const Vektor & vec):size(vec.size){
  data.resize(vec.size);
  for (int i = 0; i < size; i++)
  {
    data[i]=vec.data[i];
  }
}
Vektor& Vektor::operator|(int a)
{
  data.push_back(a);
  size=data.size();
  return *this;
}
Vektor& operator|(int a,Vektor& vec)
	{
    vec.size++;
    vec.data.resize(vec.size);
    for (int i = vec.size-1; i >=1; i--)
    {
      vec.data[i]=vec.data[i-1];
    }
    vec.data[0]=a;
    return vec;
	}
int Vektor::operator[](int index) const{
  int a=index;
  while(a>=size)
  {
    a-=size;
  }
  while(a<0)
  {
    a+=size;
  }
  return data[a];
}
int & Vektor::operator[](int index){
  while(index>=size)
  {
    index-=size;
  }
  while(index<0)
  {
    index+=size;
  }
  return data[index];
}
int Vektor::operator*(const Vektor& vec1)
  {
    if(vec1.size==0||size==0||vec1.size!=size)
      return 0;
    else
    {
      int suma=0;
      for(int i=0;i<vec1.size;i++)suma+=vec1.data[i]*data[i];
      return suma;
    }
    return 0;
  }
	std::ostream & operator<<(std::ostream & out, const Vektor& vec) {
		out << "(";
		for (int i = 0; i<vec.size; i++)
		{
			if (i<vec.size - 1)
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
    
    for(int i=0;i<size;i++){
      Vektor n;
      int nor=0;
      for(int j=i;j<size;j++)
      {
        if(abs(data[j]+nor)>x) break;
        nor+=abs(data[j]);
      }
      if(nor!=x) continue;
      for(int j=i;j<size;j++)
      {
        n|data[j];
        nor-=abs(data[j]);
        if(nor==0)return n;
      }
    }
    return novi;
}
Vektor& Vektor::operator--()
{
  if(size>0){
    data.erase(data.begin());
    size--;
  }
  return *this;
}
Vektor& Vektor::operator--(int)
{
  if(size>0){
    data.pop_back();
    size--;
  }
  return *this;
}
int Vektor::operator+()
{
  if(size==0)return 0;
  int max=0;
  for (int i = 0; i < size; i++)
  {
    if(abs(data[i])>max)
      max=abs(data[i]);
  }
  return max;
}
int Vektor::operator-()
{
  if(size==0)return 0;
  int min=INT32_MAX;
  for (int i = 0; i < size; i++)
  {
    if(abs(data[i])<min)
      min=abs(data[i]);
  }
  return min;
}
Vektor Vektor::operator&(const Vektor& vec){
  Vektor novi;
      novi.data.resize(vec.size+size);
      novi.size=vec.size+size;
      for(int i=0;i<size;i++)
        novi.data[i]=data[i];
      for(int i=0;i<vec.size;i++)
        novi.data[size+i]=vec.data[i];
      return novi;
}

