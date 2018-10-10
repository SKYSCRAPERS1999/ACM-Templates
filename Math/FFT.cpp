const int NMAX = 1<<20;

typedef complex<double> cplx;

inline cplx operator * (cplx a, cplx b) {
  double ra = a.real(), rb = b.real(),
         ia = a.imag(), ib = b.imag();
  return cplx(ra*ia-rb*ib, ra*ib+rb*ia);
}

const double PI = 2*acos(0.0);
struct FFT{
    int rev[NMAX];
    cplx omega[NMAX], oinv[NMAX];
    int K, N;

    FFT(int k){
        K = k; N = 1 << k;
        rep (i, N){
            rev[i] = (rev[i>>1]>>1) | ((i&1)<<(K-1));
            omega[i] = polar(1.0, 2.0 * PI / N * i);
            oinv[i] = conj(omega[i]);
        }
    }

    void dft(cplx* a, cplx* w){
        rep (i, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int l = 2; l <= N; l *= 2){
            int m = l/2;
            for (cplx* p = a; p != a + N; p += l)
                rep (k, m){
                    cplx t = w[N/l*k] * p[k+m];
                    p[k+m] = p[k] - t; p[k] += t;
                }
        }
    }

    void fft(cplx* a){dft(a, omega);}
    void ifft(cplx* a){
        dft(a, oinv);
        rep (i, N) a[i] /= N;
    }

    void conv(cplx* a, cplx* b){
        fft(a); fft(b);
        rep (i, N) a[i] *= b[i];
        ifft(a);
    }

    void convr(cplx* a, cplx* b) {
      rep (i, N) b[i].imag(a[i]);
      fft(b);
      rep (i, N) {
        cplx lv = b[i], rv = conj(b[N-1-i]);
        a[i] = (lv * lv + rv * rv) * cplx(0, -0.25);
      }
      ifft(a);
    } 
};

