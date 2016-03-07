#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using vi = vector<int>;

vi longestIncresing(vi array) {
  vi S = {0};
  vi parent(array.size(), -1);
  for(int i = 1; i < array.size(); ++i) {
    int val = array[i];
    if(val > array[S.back()]) {
      parent[i] = S.back();
      S.push_back(i);
    } else {
      int low = 0;
      int high = S.size()-1;
      while(low != high) {
        int mid = (low + high)/2;
        if(array[S[mid]] < val) {
          low = mid + 1;
        } else {
          high = mid;
        }
      }
      S[low] = i;
      parent[i] = low > 0 ? S[low-1] : -1;
    }
  }
  vi res;
  int index = S.back();
  while(index != -1) {
    res.push_back(array[index]);
    index = parent[index];
  }
  return vi(res.rbegin(), res.rend());
}

int main() {
  int n;
  cin >> n;
  vi array(n);
  for(int i = 0; i < n; ++i) cin >> array[i];
  vi lis = longestIncresing(array);
  for(auto val : lis) cout << val << endl;
  return 0;
}