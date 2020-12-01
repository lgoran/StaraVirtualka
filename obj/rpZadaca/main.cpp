#include <bits/stdc++.h>
#include <unistd.h>
#include "vektor.h"
using namespace std;

const int MAXN = 200000;

int n, pref[MAXN];
Vektor a;

void test() {
  int first = rand()%(n / 10);
  int last = n - 1 - (rand()%(n / 10));
  int x = pref[last] - pref[first];
  Vektor b = (a % x);
}
//MAIN ZA VELIKE
int main() {
  Vektor abc;
  abc|2|1|2|3|0|0|-1|5;
  cout<<abc<<abc%10<<endl;
  
  srand(time(NULL) * getpid());
  n = 200000;

  for (int i = 0; i < n; i++) {
    int rnd = rand()%1000 - 500;
    a | rnd;
    if (!i) pref[i] = max(rnd, -rnd);
    else pref[i] = pref[i - 1] + max(rnd, -rnd);
  }

  double start = clock();
  test();
  test();

  printf("Vrijeme izvrsavanja: %.2lf sec\n",(clock()-start)/CLOCKS_PER_SEC);

//
//
//TESTNI MAIN
  Vektor v1;
    v1 | 1;
    v1 | 2;
    v1 | 3;
    v1 | 4;
    cout << v1 << endl; // (1,2,3,4)
    cout << (double)v1 << endl; // 2.5
    cout << (double)(5|v1) << endl; // 3
    cout << v1 << endl; // (5,1,2,3,4)
    cout << +(v1--) << endl; // 5
    cout << -(--v1) << endl; // 1
    cout << v1 << endl; // (1,2,3)

    Vektor v2;
    7 | v2 | 5 | 6;
    cout << v2 << endl; // (7,5,6)
    v2[0] = 7;
    v2[1] = 10;
    cout << v2 << " " << v2[1] << " " << v2[-2] << endl; // (7,10,6) 10 10
    cout << v1 * v2 << endl; // 45

    Vektor v3 = (0 | v1) & (v2 | 11);
    cout << v3 << endl; // (0,1,2,3,7,10,6,11)
    cout << v1 << endl; // (0,1,2,3)
    cout << v2 << endl; // (7,10,6,11)

    cout << v3 % 1 << endl; // (0,1)
    cout << v3 % 0 << endl; // (0)
    cout << v3 % -1 << endl; // ()

    -1 | v3;
    Vektor v4 = v3 % 14;
    cout << (v4 | 2) << endl; // (-1,0,1,2,3,7,2)

    cout << --(v1--) << endl; // (1,2)
    cout << (--(--(--(v1))))-- << endl; // ()
    cout << +v1 << " " << -v1 << " " << (double)v1 << endl; // 0 0 0
    cout << (v1 * v1) << " " << (v2 * v3) << endl; // 0 0
    cout << (v1 % 0) << endl; // ()

  return 0;
}