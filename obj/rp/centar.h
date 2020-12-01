#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>
class Artikl {
public:
	Artikl(std::string name, int price);
	std::string ime;
	int cijena;
private:
	
};
class prolazni : public Artikl {
public:
	prolazni(std::string name, int price, int days);
	int preostalo_dana;
private:
};
class trajni : public Artikl {
public:
	trajni(std::string name, int price);
private:
};
class centar {
public:
	centar();
	int ID;
	int broj_propalih=0;
	int koliko(std::string ime);
	void prosaodan();
	int propalo();
	bool dobavi(std::string ime, int koliko);
	std::pair<int, int> naruci(std::string ime, int kolicina);
	std::vector<prolazni> Prolazni;
	std::vector<trajni> Trajni;
	static int broj_centara;
	static void prosaoDan();
	static std::vector<trajni> svi_trajni;
	static std::vector<prolazni> svi_prolazni;
	static std::vector<centar> svi_centri;
private:	
};