#include <bits/stdc++.h>
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
      //binary search
      int idx = lower_bound(S.begin(),S.end(), val, [&](int a,int r){return array[a] < r;})-S.begin();
      S[idx] = i;
      parent[i] = idx > 0 ? S[idx-1] : -1;
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
