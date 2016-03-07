#include <cstdio>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

// typedef vector<int> vi;
typedef long double ld;
typedef complex<ld> com;
typedef vector<com> vc;

ld pi = acos(-1);

int approxTwo(int n) {
  n = n - 1;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  return n + 1;
}

vc FFTHelper(vc even, vc odd, com root) {
  int n = 2*even.size();
  vc res(n);

  com mult = 1;
  for(int i = 0; i < n/2; ++i) {
    res[i] = even[i] + mult*odd[i];
    res[n/2 + i] = even[i] - mult*odd[i];
    mult *= root;
  }

  return res;
}

vc FFT(vc coeff, int sign) {
  int n = coeff.size();
  if(n == 1) return coeff;

  vc even(n/2), odd(n/2);
  for(int i = 0; i < n/2; ++i) {
    even[i] = coeff[i<<1];
    odd[i]  = coeff[(i<<1) + 1];
  }

  return FFTHelper(FFT(even, sign), FFT(odd, sign), exp(com(0, sign*2*pi/n)));
}

vc invFFT(vc vals) {
  int n = vals.size();
  vc res = FFT(vals, -1);
  for(int i = 0; i < n; ++i) res[i] = res[i]/com(n);
  return res;
}

vc mult(vc a, vc b) {
  int resN = a.size() + b.size()-1;
  int n = approxTwo(resN);
  a.resize(n, com(0,0));
  b.resize(n, com(0,0));

  vc res(n);
  vc resA = FFT(a, 1);
  vc resB = FFT(b, 1);
  for(int i = 0; i < n; ++i) {
    res[i] = resA[i]*resB[i];
  }

  vc tmp = invFFT(res);
  tmp.resize(resN);
  return tmp;
}

int main() {
  vc a = {com(1), com(1)};
  vc b = {com(1), com(1)};
  // a.resize(4, com(0));
  vc c = mult(a, b);
  cout << pow(exp(com(0, pi/2)), 1) << endl;
  cout << a.size() << endl;
  cout << b.size() << endl;
  cout << c.size() << endl;
  for(int i = 0; i < c.size(); ++i) {
    cout << c[i] << endl;
  }
  return 0;
}