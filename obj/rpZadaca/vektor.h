#pragma once
#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <cmath>
#include <vector>
class Vektor {
public:
	Vektor() :size(0){}
  Vektor(const Vektor & vec);
  int operator[](int index) const;
  int & operator[](int index);
	Vektor& operator|(int a);
  Vektor& operator--();
  Vektor& operator--(int);
  inline operator double() const{
    int suma=0;
    for(int i=0;i<size;i++) suma+=data[i];
    if(suma==0) return 0;
    return static_cast<double>(suma)/size;
  }
  Vektor operator&(const Vektor& vec);
  int operator+();
  int operator-();
  int operator*(const Vektor& vec1);
	friend Vektor& operator|(int a, Vektor& vec);
	friend std::ostream & operator<<(std::ostream & out, const Vektor& vec);
  Vektor operator%(int x);
	std::vector<int> data;
	long int size;
};


  #endif
