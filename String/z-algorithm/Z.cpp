#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using vi = vector<int>;
// vector<int> Z(string str) {
//   vector<int> z(str.size(), 0);
//   int S, L;
//   z[0] = str.size();
//   S = L = 0;
//   for(int i = 1; i < str.size(); ++i) {
//     int k = i - S;
//     if(k+z[k] > L) {
//       S = i;
//       L = max(0, L - k);
//       while(str[i + L] == str[L]) ++L;
//       z[i] = L;
//     } else {
//       z[i] = z[k];
//     }
//   }
//   return z;
// }


vi Z(string &str) {
  vi z(str.size(), 0);
  int L, R;
  z[0] = str.size();
  L = 1, R = 1;
  for(int k = 1; k < str.size(); ++k) {
    if(k + z[k - L] < R) {
      z[k] = z[k - L]; 
    } else { 
      L = k;
      R = max(R, k);
      while(R < str.size() && str[R - L] == str[R]) ++R;
      z[k] = R - L;
    }
  }
  return z;
}

int main() {
  vector<int> z = Z("abcabcabcabc");
  for(int s : z) cout << s << endl;
  return 0;
}