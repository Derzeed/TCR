#include <bits/stdc++.h>

using namespace std;

int modExp(int base, int exponent, int modulus) {
  int res = 1;
  base = base % modulus;
  while(exponent > 0) {
    if(exponent%2 == 1) {
      res = (res*base)%modulus;
    }
    exponent = exponent >> 1;
    base = (base*base)%modulus;
  }
  return res;
}

// vector<int> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23}; // if n < 3*10^18
vector<int> bases = {2, 7, 61}; // if n < 2*10^9
bool MillerRabin(int n) {
  int d = n-1;
  int s = 0;
  while(d%2 == 0) {
    ++s;
    // cout << s << " " << d << endl;
    d = d >> 1;
  }


  for(auto base : bases) {
    if(n == base) return true;
    int m = modExp(base, d, n);
    if(m == 1 || m == n-1) continue;
    bool prime = false;
    for(int i = 0; i < s && !prime; ++i) {
      m = (m*m)%n;
      if(m == 1) return false;
      else if(m == n-1) prime = true;
    }
    if(!prime) return false;
  }
  return true;
}

int main() {
  int t;
  cin >> t;
  while(t --> 0) {
    int u, l;
    cin >> l >> u;
    if(l == 1) ++l;
    while(l <= u) {
      if(MillerRabin(l)) {
        printf("%d\n", l);
      }
      ++l;
    }
  }

  return 0;
}