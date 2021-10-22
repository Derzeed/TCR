#include<bits/stdc++.h>
using namespace std;
#define MP(a, b) make_pair(a, b)
#define FOR(i, n) for(int i = 0; i < (ll)(n); i++)
#define FORE(x,a) for(auto &x: a)
#define FORT(i,a,b) for(int i=(a);i<(b);i++)
#define ALL(x) x.begin(),x.end()
typedef long double ld;
typedef long long ll;

ld eps = 1e-9;

template<class T, T mod> struct ModInt {
    T x;
    ModInt() : x(0) {}
    ModInt(T x) : x((x % mod + mod) % mod) {}
    operator T() const { return x; }
    ModInt operator-() { return ModInt(-*this); }
    ModInt& operator+=(const ModInt& a) { x = (x + a.x) % mod; return *this; }
    ModInt& operator-=(const ModInt& a) { x = ((x - a.x) % mod + mod) % mod; return *this; }
    ModInt& operator*=(const ModInt& a) { x = (x * a.x) % mod; return *this; }
    ModInt& operator/=(const ModInt& a) { *this *= a.inv(); return *this; }
    ModInt operator+(const ModInt& a) { return ModInt(*this) += a; }
    ModInt operator-(const ModInt& a) { return ModInt(*this) -= a; }
    ModInt operator*(const ModInt& a) { return ModInt(*this) *= a; }
    ModInt operator/(const ModInt& a) { return ModInt(*this) /= a; }
    bool operator==(const ModInt& a) { return x == a.x; }
    bool operator!=(const ModInt& a) { return x != a.x; }
    friend istream& operator>>(istream& i, ModInt& a) { T t; i >> t; a = t; return i; }
    ModInt inv() const {
        T a = x, b = mod, u = 1, v = 0;
        while(b) {
            int t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }
};

template<class T> struct Matrix {
    int M, N;
    vector<T> data;
    Matrix() : M(0), N(0) {}
    Matrix(int M, int N) : M(M), N(N) { data = vector<T>(M * N); }
    Matrix(initializer_list<initializer_list<T>> a) : Matrix(a.size(), a.begin()->size()) {
        int i = 0; FORE(l,a) copy(ALL(l), (*this)[i]), i++;
    }
    T* operator[](int i) { return &data[i * N]; }
    const T* operator[](int i) const { return &data[i * N]; }
    friend ostream &operator<<(ostream &o, const Matrix &a) {
        if (a.M == 0 || a.N == 0) return o << "[[]]";
        o << '[';
        FOR(i, a.M) {
            o << '[';
            FOR(j, a.N) o << a[i][j] << ", ";
            o << "\b\b], ";
        }
        return o << "\b\b]";
    }
    bool operator==(const Matrix& a) {
        if (this->M != a.M || this->N != a.N) return false;
        FOR(i, a.M)
            FOR(j, a.N)
                if (abs((*this)[i][j] - a[i][j]) > eps) return false;
        return true;
    }
    bool operator!=(const Matrix& a) { return !(*this == a); }

    friend Matrix matmul(const Matrix& a, const Matrix& b) {
        assert(a.N == b.M);
        Matrix res(a.M, b.N);
        FOR(i, a.M)
            FOR(j, a.N)
                FOR(k, b.N)
                    res[i][k] += a[i][j] * b[j][k];
        return res;
    }

    friend Matrix pow(const Matrix& a, ll n) {
        int M = a.M, N = a.N;
        assert(M == N);
        Matrix res(N, N);
        FOR(i,N)
            res[i][i] = 1;
        Matrix p = a;
        while(n) {
            if(n & 1) res = matmul(p, res);
            p = matmul(p, p);
            n >>= 1;
        }
        return res;
    }

    Matrix rref() const { // reduced row echelon form
        Matrix a = *this;
        for (int col = 0, row = 0; col < M && row < N; col++) {
            int piv = row;
            FORT(i, row, M) if (abs(a[i][col]) > abs(a[piv][col])) piv = i;
            if (abs(a[piv][col]) < eps) continue;
            FOR(j, N) swap(a[piv][j], a[row][j]);
            T p = a[row][col];
            FOR(j, N) a[row][j] /= p;
            FOR(i, M) {
                if (i == row) continue;
                T c = a[i][col] / a[row][col];
                FOR(j, N) {
                    a[i][j] -= a[row][j] * c;
                }
            }
            row++;
        }
        return a;
    }

    friend Matrix augment(Matrix a, Matrix b) {
        assert(a.M == b.M);
        Matrix aug(a.M, a.N + b.N);
        FOR(i, a.M)
            FOR(j, a.N)
                aug[i][j] = a[i][j];
        FOR(i, a.M)
            FOR(j, b.N)
                aug[i][a.N + j] = b[i][j];
        return aug;
    }

    // Find solution (column vector) and rank of SLE. Returns 0x0 Matrix if SLE is inconsistent
    friend pair<Matrix, int> solve_sle(Matrix A, Matrix b) {
        assert(b.N == 1);
        Matrix soln = augment(A, b).rref();
        int n = soln.N - 1;
        int rank = 0;
        while(rank < min(soln.M, soln.N)) {
            bool zero_row = true;
            FOR(j, soln.N - 1) zero_row &= abs(soln[rank][j]) < eps;
            if (zero_row) break;
            rank++;
        }
        Matrix x(n, 1);
        for (int row = 0, col = 0; row < soln.M; row++) {
            while (col < n && abs(soln[row][col] - 1) > eps) col++;
            if (col == n) break;
            x[col][0] = soln[row][n];
        }
        if (matmul(A, x) != b) return MP(Matrix(0,0), rank);
        return MP(x, rank);
    }
};

using mint = ModInt<ll, (int)1e9 + 7>;
using mmat = Matrix<mint>;
using fmat = Matrix<ld>;
using imat = Matrix<ll>;

int main() {
    // matrix exponentiation
    imat fibonacci_matrix = {{1, 1}, {1, 0}};
    FOR(i, 50) {
        ll fib_i = pow(fibonacci_matrix, i)[1][0];
        cout << fib_i << endl;
    }

    // reduced row echelon form
    mmat cool_matrix(4, 8);
    FOR(i, cool_matrix.M) {
        FOR(j, cool_matrix.N) {
            cool_matrix[i][j] = i * cool_matrix.N + j;
        }
    }
    mmat reduced_row_echelon_form = cool_matrix.rref();
    cout << cool_matrix << endl;
    cout << reduced_row_echelon_form << endl;

    // solve system of linear equations
    int n;
    cin >> n;
    fmat A(n, n);
    fmat b(n, 1);
    FOR(i, n)
        FOR(j, n)
            cin >> A[i][j];
    FOR(i, n)
        cin >> b[i][0];

    fmat x;
    int rank;
    tie(x, rank) = solve_sle(A, b);
    if (x.M == 0) {
        cout << "no solution, SLE is inconsistent" << endl;
    } else if (rank < n) {
        cout << "multiple solutions, here's one:" << endl;
        cout << x << endl;
    } else {
        cout << "single solution:" << endl;
        cout << x << endl;
    }
}

