const int maxn = 1000 + 11;
const int MOD = 1e9 + 7;
int N, M, K;
//a_k = \sum_{i=0}^{k-1}(c_i a_i)
//Given a_0,...,a_{k-1}; c_0, ..., c_{k-1}
//O(n^2logk)
LL c[maxn<<1], a[maxn<<1], tmp[maxn<<1];
inline void mul(LL *A, LL *B){
    fill(tmp, tmp + 2*K-1, 0);
    for (int i = 0; i < K; i++){
        for (int j = 0; j < K; j++){
            tmp[i+j] = (tmp[i+j] + A[i]*B[j]) % MOD;
        }
    }
    for (int i = 2*(K-1); i >= K; i--){
        for (int j = 0; j < K; j++){
            tmp[i-K+j] = (tmp[i-K+j] + tmp[i]*c[j]) % MOD;
        }
        tmp[i] = 0;
    }
    copy(tmp, tmp + 2*K-1, A);
}
void qpow(LL *A, int n){
    LL ret[maxn<<1]; ret[0] = 1;
    while (n){
        if (n&1) mul(ret, A);
        mul(A, A);
        n >>= 1;
    }
    copy(ret, ret + K, A);
}
int main(){
    cin >> K >> N;
    N--;
    for (int i = 0; i < K; i++) cin >> a[i];
    for (int i = 0; i < K; i++) cin >> c[i];
    LL b[maxn<<1] = {0,1,};
    qpow(b, N);

    LL ans = 0;
    for (int i = 0; i < K; i++) ans = (ans + b[i] * a[i]) % MOD;
    cout << ans << endl;
    return 0;
}
