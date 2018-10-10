inline int add(int x) {return x >= MOD ? x - MOD : x;}
inline int sub(int x) {return x < 0 ? x + MOD : x;}
inline int mul(int x, int y) {return (long long) x * y % MOD;}
inline int pwr(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x)) {
        if (y & 1) ans = mul(ans, x);
    }
    return ans;
}

LL inv[maxn], fac[maxn], invf[maxn];
inline LL C(LL x, LL y) {
    return ((fac[x] * invf[y]) % MOD * invf[x - y]) % MOD;
}
void init(){
    invf[0] = inv[0] = inv[1] = fac[0] = fac[1] = 1;
    for (LL i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % MOD;
    for (int i = 2; i < maxn; i++) inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 1; i < maxn; i++) invf[i] = invf[i - 1] * inv[i] % MOD;
}
