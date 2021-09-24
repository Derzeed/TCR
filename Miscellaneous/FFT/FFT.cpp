#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef complex<ld> com;
typedef vector<com> vc;
const ld pi = acos(-1);

int approxTwo(int n) {
    return 1 << (32 - __builtin_clz(n - 1));
}

void bit_rev(vc &a) {
    int n = a.size();
    int j = 0;
    for (int i = 1; i < n; i++) {
        int bit = n >> 1;
        while(j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }
}

void fft(vc &a, int sign = 1) {
    int n = a.size();
    bit_rev(a);
    for (int len = 2; len <= n; len *= 2) {
        ld theta = sign * 2 * pi / len;
        com root(cos(theta), sin(theta));
        for (int i = 0; i < n; i += len) {
            com w = 1.0;
            for (int j = 0; j < len/2; j++) {
                com even = a[i + j];
                com odd = w * a[i + j + len/2];
                a[i + j] = even + odd;
                a[i + j + len/2] = even - odd;
                w *= root;
            }
        }
    }
}

void ifft(vc &a) {
    fft(a, -1);
    for (auto &it : a) it /= a.size();
}

vc conv(vc a, vc b) {
    int n = a.size() + b.size() - 1;
    int n2 = approxTwo(n);

    a.resize(n2);
    b.resize(n2);
    fft(a);
    fft(b);

    for (int i = 0; i < n2; i++) {
        a[i] *= b[i];
    }
    ifft(a);
    a.resize(n);
    return a;
}

int main() { // Tested on https://open.kattis.com/problems/polymul2
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        n++;
        vc a(n);
        for (auto &it : a) cin >> it;

        int m; cin >> m;
        m++;
        vc b(m);
        for (auto &it : b) cin >> it;

        vc res = conv(a, b);
        cout << res.size() - 1 << endl;
        for (int i = 0; i < res.size(); i++) {
            cout << (ll)round(res[i].real()) << " \n"[i == res.size()-1];
        }
    }
}

