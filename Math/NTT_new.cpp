const int P = 998244353;
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
