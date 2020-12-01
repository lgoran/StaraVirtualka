#include "centar.h"
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
vector<trajni>centar::svi_trajni{};
vector<prolazni> centar::svi_prolazni{};
vector<centar> centar::svi_centri{};
bool sortbysec(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.second < b.second); 
} 
bool jeli_prolazan(string ime)
{
	for(int j=0;j<centar::svi_centri.size();j++)
	for(int i=0; i<centar::svi_centri[j].Prolazni.size();i++)
	{
		if(ime==centar::svi_centri[j].Prolazni[i].ime)
			return true;
	}
	return false;
}
Artikl::Artikl(std::string name, int price) : ime(name), cijena(price)
{

}

prolazni::prolazni(std::string name, int price, int days) : Artikl(name,price),preostalo_dana(days)
{
	centar::svi_prolazni.push_back(*this);
}

trajni::trajni(std::string name, int price) : Artikl(name,price)
{
	centar::svi_trajni.push_back(*this);
}

centar::centar() : ID(broj_centara)
{
	broj_centara++;
	svi_centri.push_back(*this);
}
int centar::propalo()
{
	for(int i=0;i<svi_centri.size();i++)
		if(ID == svi_centri[i].ID)
			*this=svi_centri[i];
	 return broj_propalih;
}
int centar::koliko(std::string ime)
{
	*this=svi_centri[ID];
	int a = 0;
	for (int i = 0; i < Prolazni.size(); i++)
		if (Prolazni[i].ime == ime) a++;
	for (int i = 0; i < Trajni.size(); i++)
		if (Trajni[i].ime == ime) a++;
	return a;
}
void centar::prosaodan()
{
	int prop = 0;
	for (int i = Prolazni.size()-1; i >=0;i--)
	{
		Prolazni[i].preostalo_dana--;
		if (Prolazni[i].preostalo_dana < 0) {
			prop+=Prolazni[i].cijena;
			Prolazni.erase(Prolazni.begin() + i);
		}
	}
	broj_propalih = prop;
	svi_centri[ID]=*this;
}
bool centar::dobavi(std::string ime, int koliko)
{
	*this=svi_centri[ID];
	bool flag = false;
	for (int i = 0; i < svi_prolazni.size(); i++)
	{
		if (ime == svi_prolazni[i].ime)
		{
			flag=true;
			for(int j=0;j<koliko;j++)
			Prolazni.push_back(svi_prolazni[i]);
		}
	}
	for (int i = 0; i < svi_trajni.size(); i++)
	{
		if (ime == svi_trajni[i].ime)
		{
			flag=true;
			for(int j=0;j<koliko;j++)
			Trajni.push_back(svi_trajni[i]);
		}
	}
	svi_centri[ID]=*this;
	return flag;
}
pair<int, int> centar::naruci(std::string ime, int kolicina)
{
	pair<int, int> par;
	*this=svi_centri[ID];
	//vektor za pronaci najmanje
	pair<int, int> pom;
	vector< pair<int, int> > dani_id;
	for(int i=0;i<svi_centri.size();i++)
	{
		for(int j=0;j<svi_centri[i].Prolazni.size();j++)
		{
			if(svi_centri[i].Prolazni[j].ime == ime)
				dani_id.push_back(make_pair(i,svi_centri[i].Prolazni[j].preostalo_dana));
		}
	}
	sort(dani_id.begin(), dani_id.end(), sortbysec); 
	int kn = 0;
	int kol=kolicina;
	if (koliko(ime) >= kolicina)
	{
		for (int i = Trajni.size()-1; i >= 0;i--)
		{
			if (ime == Trajni[i].ime && kol>0)
			{	
				kol--;
				kn += Trajni[i].cijena;
				Trajni.erase(Trajni.begin()+i);
			}
		}
		for (int i = Prolazni.size()-1; i >= 0;i--)
		{
			if (ime == Prolazni[i].ime && kol>0)
			{
				kol--;
				kn += Prolazni[i].cijena;
				Prolazni.erase(Prolazni.begin()+i);
			}
		}
		svi_centri[ID]=*this;
		par.first=kolicina;
		par.second=kn;
		return par;
		
	}
	else if(jeli_prolazan(ime)){
		for (int i = Prolazni.size()-1; i >= 0;i--)
		{
			if (ime == Prolazni[i].ime && kol>0)
			{
				kol--;
				kn += Prolazni[i].cijena;
				Prolazni.erase(Prolazni.begin()+i);
			}
		}
		svi_centri[ID]=*this;
		vector<int> unutra;
		for(int i=0;i<dani_id.size();i++)
		{
			if(dani_id[i].first == ID)
			{continue;}
			else if(kol>0)
			{
				int jeli_preuzeto=0;
				for(int j=svi_centri[dani_id[i].first].Prolazni.size()-1;j>=0;j--)
				{
					if(svi_centri[dani_id[i].first].Prolazni[j].ime == ime && kol>0 && svi_centri[dani_id[i].first].Prolazni[j].preostalo_dana== dani_id[i].second)
					{
						kn+=svi_centri[dani_id[i].first].Prolazni[j].cijena;
						kol--;
						jeli_preuzeto=1;
						svi_centri[dani_id[i].first].Prolazni.erase(svi_centri[dani_id[i].first].Prolazni.begin()+j);
						break;												
					}
				}
				Prolazni=svi_centri[ID].Prolazni;
				if(jeli_preuzeto==1)
				{
					if(find(unutra.begin(), unutra.end(), dani_id[i].first) == unutra.end())
					{
						kn++;
						unutra.push_back(dani_id[i].first);
					}
					dani_id.erase(dani_id.begin()+i);
					i--;
				}
			}
		}
	}
	else if(!jeli_prolazan(ime)){
		for (int i = Trajni.size()-1; i >= 0;i--)
		{
			if (ime == Trajni[i].ime && kol>0)
			{
				kol--;
				kn += Trajni[i].cijena;
				Trajni.erase(Trajni.begin()+i);
			}
		}
		for (int i = 0; i < svi_centri.size(); i++)
		{
			if(svi_centri[i].ID==ID)
			{continue;}
			else if(kol>0)
			{
				int jeli_preuzeto=0;				
				for(int j=svi_centri[i].Trajni.size()-1;j>=0;j--)
				{
					if(svi_centri[i].Trajni[j].ime == ime && kol>0)
					{
						kn+=svi_centri[i].Trajni[j].cijena;
						kol--;
						jeli_preuzeto=1;
						svi_centri[i].Trajni.erase(svi_centri[i].Trajni.begin()+j);
					}
				}
				if(jeli_preuzeto==1) kn++;
				Trajni=svi_centri[ID].Trajni;
			}
		}
	}
	svi_centri[ID]=*this;
	if(kol>0)
		dobavi(ime,kol);
	par.first=kolicina-kol;
	par.second=kn;
	return par;
}
void centar::prosaoDan()
{
	for(int i=0;i<svi_centri.size();i++)
	svi_centri[i].prosaodan();
}
int centar::broj_centara = 0;

