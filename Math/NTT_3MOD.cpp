#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int INF = 0x3f3f3f3f;
const int maxn = 1e5 + 11;
int N, M, T;

int P = 998244353;
const LL G = 3;
#define rep(i,n) for(int i=0;i<(n);i++)
#define Rep(i,a,b) for(int i=(a);i<(b);i++)
typedef vector<LL> vl;
int get(int s) { return s > 1 ? 32 - __builtin_clz(s - 1) : 0;}
namespace NTT {
    LL qpow(LL b, LL p) { return !p?1:qpow(b*b%P,p/2)*(p&1?b:1)%P; }
    LL inv(LL b) { return qpow(b,P-2); }

    void ntt(vl& a) {
        int n = a.size(), x = get(n);
        vl b(n), omega(n);
        omega[0] = 1, omega[1] = qpow(G,(P-1)/n);
        Rep(i,2,n) omega[i] = omega[i-1]*omega[1] % P;
        Rep(i,1,x+1){
            int inc=n>>i;
            rep(j,inc) for(int k=0;k<n;k+=inc){
                int t = 2*k%n+j;
                b[k+j] = (a[t]+omega[k]*a[t+inc]) % P;
            }
            swap(a,b);
        }
    }

    void ntt_rev(vl& a) {
        ntt(a);
        LL r = inv(a.size());
        rep(i,a.size()) a[i] = a[i] * r % P;
        reverse(a.begin() + 1, a.end());
    }

    vl brute(vl& a, vl& b) {
        vl c(a.size()+b.size()-1);
        rep(i,a.size()) rep(j,b.size()) c[i+j] = (c[i+j]+a[i]*b[j])%P;
        return c;
    }

    vl conv(vl a, vl b) {
        int s = a.size()+b.size()-1, L = get(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return brute(a,b);

        a.resize(n); ntt(a);
        b.resize(n); ntt(b);

        rep(i,n) a[i] = a[i] * b[i] % P;
        ntt_rev(a);

        a.resize(s);
        return a;
    }
}

const int MOD = 1e9 + 7;
const int MO[] = {0, 998244353,1004535809,469762049};
const ULL MO1_MO2 = 1002772198720536577ULL;
const int MO1_INV_MO2 = 669690699; /*modPow<MO2>(MO1, MO2 - 2)*/
const int MO2_INV_MO1 = 332747959; /*modPow<MO1>(MO2, MO1 - 2)*/
const int MO1_MO2_INV_MO3 = 354521948;
/*modPow<MO3>(MO1_MO2 % MO3, MO3 - 2)*/
const int MO1_MO2_MOD = 701131240;/*MO1_MO2 % MOD*/
inline int crt(int a1, int a2, int a3) {
    ULL a = ((ULL)MO[2] * ((ULL)a1 * MO2_INV_MO1 % MO[1]) +
               (ULL)MO[1] * ((ULL)a2 * MO1_INV_MO2 % MO[2])) % MO1_MO2;
	return (a + (MO[3] + a3 - a % MO[3]) % MO[3] *
            MO1_MO2_INV_MO3 % MO[3] * MO1_MO2_MOD % MOD) % MOD;
}

vl C[4];
int main(){
    scanf("%d%d", &N, &M);
    vl A(N + 1, 0), B(M + 1, 0);
    for (int i = 0; i <= N; i++) scanf("%d", &A[i]);
    for (int i = 0; i <= M; i++) scanf("%d", &B[i]);
    for (int i = 1; i <= 3; i++) {
        P = MO[i];
        C[i] = NTT::conv(A, B);
    }
    for (int i = 0; i <= N + M; i++) printf("%d%c", crt(C[1][i],C[2][i],C[3][i]), " \n"[i==N+M]);
    return 0;
}
/*
1 2
1 2
1 2 1

*/

