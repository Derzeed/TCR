#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#define MT(args...) make_tuple(args)

using namespace std;

typedef vector<int> vi;

// returns a % b(posive value)
int mod(int a, int b) {
  return ((a % b) + b) % b;
}

// computes gcd(a, b)
int gcd(int a, int b) {
  while(b) {
    tie(a, b) = MT(b, a % b);
  }
  return a;
}

// computes lcm(a, b)
int lcm(int a, int b) {
  return a/gcd(a, b)*b;
}

// returns gcd(a,b) and finds x and such that gcd(a,b) = ax + by
int extGcd(int a, int b, int &x, int &y) {
  int xx = 0; x = 1;
  int yy = 1; y = 0;
  while(b) {
    int q = a/b;
    tie(a, b)  = MT(b, a - q*b);
    tie(x, xx) = MT(xx, x - q*xx);
    tie(y, yy) = MT(yy, y - q*yy);
  }
  return a;
}

// computes b such that ab = 1 (mod n), return -1 if not possible
int mod_inverse(int a, int n) {
  int x, y;
  int d = extGcd(a, n, x, y);
  if(d > 1) return -1;
  return mod(x, n);
}

// computes a z such that z = a[i] (mod m[i]) for all i, return -1 if not possible
int chineseRemainderTheorem(vi a, vi mod) {
  int M = 1;
  for(auto m : mod) M = lcm(m,M);

  int res = 0;
  for(int i = 0; i < mod.size(); ++i) {
    int m = mod[i];
    int b = mod_inverse(M/m, m);
    if(b == -1) return -1;
    res = (res + a[i]*b*M/m)%M;
  }
  return res;
}

int main() {
  int x, y;
  int d = extGcd(3, 20, x, y);
  cout << x << "*3 + " << y << "*20 = " << d << endl;
  cout << chineseRemainderTheorem(vi({1,2,3,4,5}), vi({2,3,5,7,11})) << endl;
  // cout << t << endl;
  return 0;
}