#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(x,n) for(int x=0;x<(n);x++)
#define FORT(x,a,b) for(int x=(a);x<(b);x++)

#define val long double
#define vec vector<val>
#define mat vector<vec>

mat mat_new(ll M, ll N) {
    return mat(M, vec(N));
}

mat mat_mult(mat &A, mat &B) {
    ll L = A.size(), M = B.size(), N = B[0].size();
    mat C = mat_new(L, N);
    FOR(l, L) FOR(n, N) FOR(m, M)
        C[l][n] += A[l][m] * B[m][n];
    return C;
}

mat mat_exp(mat &A, ll exp) {
    if (exp == 1) return A;
    mat B = mat_exp(A, exp / 2);
    B = mat_mult(B, B);
    if (exp % 2 == 1) {
        return mat_mult(A, B);
    } else {
        return B;
    }
}

/* Destroys A and B, so they are pass-by-value */
vec mat_gauss_elim(mat A, vec B) {
    ll m = A.size(), n = A[0].size(), h = 0, k = 0;

    /* any matrix -> upper-triangular */
    while(h < m && k < n) {
        ll i_max = h;
        FORT(i, h, m) if(abs(A[i_max][k]) < abs(A[i][k])) i_max = i;
        if(A[i_max][k] == 0) {
            k++;
            continue;
        }
        swap(B[i_max], B[h]);
        A[i_max].swap(A[h]);
        FORT(i, h+1, m) {
            val f = A[i][k] / A[h][k];
            A[i][k] = 0;
            FORT(j, k+1, n) {
                A[i][j] -= A[h][j] * f;
            }
            B[i] -= B[h] * f;
        }
        h++;
        k++;
    }

    /* upper-triangular -> solution */
    h = m - 1;
    vec C = vec(n);
    while (h >= 0) {
        ll k = -1;
        FOR(i, n) if (A[h][i] != 0) { k = i; break; }
        if (k == -1) { h--; continue; }

        val f = 1.0 / A[h][k];
        FORT(i, k, n)
            A[h][i] *= f;
        B[h] *= f;
        FORT(i, k+1, n) {
            val g = A[h][i];
            A[h][i] = 0;
            B[h] -= g * C[i];
        }
        C[k] = B[h];

        if(k == 0) break;
        h--;
    }
    return C;
}

void mat_print_total(mat &A, vec &B) {
    ll m = A.size(), n = A[0].size();
    FOR(i, m) {
        FOR(j, n)
            cout << A[i][j] << " ";
        cout << "= " << B[i] << endl;
    }
}


/* Solution to NCPC 2021 Problem F */
/* https://ncpc21.kattis.com/problems/fortunefromfolly */

ll bits(ll b) {
    return b == 0 ? 0 : bits(b / 2) + b % 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k;
    val p;
    cin >> n >> k >> p;

    ll N = pow(2, n);
    mat A = mat_new(N, N);
    vec B = vec(N);

    FOR(i, N)
        if (bits(i) >= k) {
            A[i][i] = 1;
        } else {
            A[i][i] += 1;
            A[i][(i * 2 + 1) % N] += - p;
            A[i][(i * 2) % N] += p - 1.0;
            B[i] = 1;
        }

    vec C = mat_gauss_elim(A, B);
    cout.precision(18);
    cout << C[0] << endl;
}
