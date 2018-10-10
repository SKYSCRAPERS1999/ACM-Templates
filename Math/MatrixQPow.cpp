const LL INF = 0x3f3f3f3f3f3f3f3f;
const int maxt = 100 + 3;
const int MOD = 1e9 + 7;
int N, M, T;
struct Mat{
    LL a[maxt][maxt]; int n;
    Mat(int n):n(n){}
    void clr(){memset(a, 0, sizeof(a));}
    void eye(){memset(a, 0, sizeof(a)); for (int i = 0; i < n; i++) a[i][i] = 1LL;}
    void maxi(){memset(a, 0x3f, sizeof(a));}
};
Mat cal_mul(Mat A, Mat B){
    int n = A.n;
    Mat C = Mat(n); C.clr();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
            }
        }
    }
    return C;
}
Mat qpow(Mat A, int n){
    Mat res = Mat(A.n); res.eye();
    while (n > 0){
        if (n & 1) res = cal_mul(res, A);
        A = cal_mul(A, A);
        n >>= 1;
    }
    return res;
}
