#define rep(i,n) for(int i=0;i<(n);i++)
typedef complex<double> cplx;
typedef vector<cplx> vc;
const int NMAX = 1 << 21;
int get(int s) { return s > 1 ? 32 - __builtin_clz(s - 1) : 0;}
struct FFT{
    int rev[NMAX];
    cplx omega[NMAX], oinv[NMAX];
    void dft(vc &a, cplx* w){
        int n = a.size();
        rep (i, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int l = 2; l <= n; l *= 2){
            int m = l/2;
            for (int p = 0; p < n; p += l)
                rep (k, m){
                    cplx t = w[n/l*k] * a[p+k+m];
                    a[p+k+m] = a[p+k] - t; a[p+k] += t;
                }
        }
    }
    void fft(vc &a){ dft(a, omega); }
    void ifft(vc &a){
        int n = a.size();
        dft(a, oinv);
        rep (i, n) a[i] /= n;
    }
    vc brute(vc& a, vc& b) {
        vc c(a.size()+b.size()-1);
        rep(i,a.size()) rep(j,b.size()) c[i+j] += a[i]*b[j];
        return c;
    }
    vc conv(vc a, vc b){
        int s = a.size()+b.size()-1, k = get(s), n = 1<<k;
        if (s <= 0) return {};
        if (s <= 200) return brute(a,b);
        rep (i, n){
            rev[i] = (rev[i>>1]>>1) | ((i&1)<<(k-1));
            omega[i] = polar(1.0, 2.0 * PI / n * i);
            oinv[i] = conj(omega[i]);
        }
        a.resize(n); fft(a);
        b.resize(n); fft(b);
        rep(i,n) a[i] *= b[i];
        ifft(a);
        a.resize(s);
        return a;
    }
} fft;

