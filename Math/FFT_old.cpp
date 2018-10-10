#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<bitset>
#include<cstdlib>
#include<cmath>
#include<set>
#include<list>
#include<deque>
#include<map>
#include<queue>
#include<sstream>
#include<complex>

#define lowbit(x) ((-x)&(x))
using namespace std;
typedef long long LL;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int maxn = 1e7 + 3;
int N, M, T, K, logM;
complex<double> A[4*maxn], B[4*maxn];
void FFT(int n, complex<double>* x, int dir){
    if (n == 1) return;
    int m = (n >> 1);
    complex<double> *a = new complex<double> [m];
    complex<double> *b = new complex<double> [m];
    for (int i = 0; i < m; i++) {a[i] = x[2 * i]; b[i] = x[2 * i + 1];}
    FFT(m, a, dir); FFT(m, b, dir);
    complex<double> w(1,0), wn(cos(2*PI/n), dir * sin(2*PI/n));
    for (int i = 0; i < m; i++){
        x[i] = a[i] + w * b[i];
        x[i + m] = a[i] - w * b[i];
        w *= wn;
    }
}
void solve_rec(){
    FFT(M, A, 1); FFT(M, B, 1);
    for (int i = 0; i < M; i++) {B[i] *= A[i];}
    FFT(M, B, -1);
    for (int i = 0; i < M; i++) {B[i] /= M;}
    for (int i = 0; i < 2*N-1; i++) {printf("%.10f\n", B[i].real());}
}
void bit_reverse(int *x){
    for (int i = 0; i < M; i++){
        int tmp = x[i], cur = 0;
        for (int j = 0; j < logM; j++, tmp >>= 1) cur = (cur << 1) | (tmp & 1);
        x[i] = cur;
    }
}
void fft(complex<double> *x, int* P, int dir){
    complex<double> *xx = new complex<double>[M];
    for (int i = 0; i < M; i++){xx[i] = x[i];}
    for (int i = 0; i < M; i++) {x[P[i]] = xx[i];}
    int m = 1;
    for (int s = 1; s <= logM; s++){
        m <<= 1;
        complex<double> wm(cos(2*PI/m), dir * sin(2*PI/m));
        for (int k = 0; k < M; k += m){
            complex<double> w(1, 0);
            for (int j = 0; j < (m >> 1); j++){
                complex<double> t = w * x[k + j + (m >> 1)];
                complex<double> u = x[k + j];
                x[k + j] = u + t;
                x[k + j + (m >> 1)] = u - t;
                w *= wm;
            }
        }
    }
}
void solve_iter(){
    int *P = new int[M];
    for (int i = 0; i < M; i++) {P[i] = i;}
    bit_reverse(P);
    fft(A, P, 1); fft(B, P, 1);
    for (int i = 0; i < M; i++) {B[i] *= A[i];}
    fft(B, P, -1);
    for (int i = 0; i < M; i++){B[i] /= M;}
    for (int i = 0; i < 2*N-1; i++){printf("%.10f\n", B[i].real());}
    cout << endl;
}
int main(){
    cin >> N;
    for (M = 1, logM = 0; M < 2 * N; M <<= 1, logM++);
    for (int i = 0; i < M; i++) {A[i] = B[i] = (0.0, 0.0);}
    for (int i = 0; i < N; i++) {cin>>A[i];}
    for (int i = 0; i < N; i++) {cin>>B[i];}
    solve_iter();
    return 0;
}
/*
5
1 2 3 4 5
1 2 3 4 5

*/
