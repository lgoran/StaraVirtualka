#include <iostream>
#include <utility>
#include "centar.h"
using namespace std;
ostream& operator<<(ostream& o,const pair<int, int> &p){
	o<<"("<<p.first<<","<<p.second<<")";return o;
}
void radi()
{
	centar c0,c1,c2,c3;
	pair<int, int> r;
	cout<<c1.naruci("mliko",5)<<endl;
	cout<<c1.naruci("mliko",1)<<endl;
	cout<<c2.naruci("mliko",2)<<endl;

	cout<<c3.naruci("kruh",2)<<endl;
	cout<<c1.naruci("kruh",1)<<endl;
	centar::prosaoDan();

	cout<<c0.dobavi("mliko",2)<<endl;
	cout<<c2.dobavi("dnvjsf",2)<<endl;
	cout<<c1.propalo()<<" "<<c2.propalo()<<" "<<c3.propalo()<<endl;

	centar::prosaoDan();

	cout<<c1.koliko("kdjnfhvfji")<<endl;
	cout<<c1.koliko("mliko")<<endl;
	cout<<c2.naruci("mliko",1)<<endl;
	cout<<c2.naruci("mliko",2)<<endl;
}

int main()
{
		trajni p("papuce",100), tv("tv",1000);
		prolazni m("mliko",7,7),kruh("kruh",10,0);		
		radi();
    return 0;
}