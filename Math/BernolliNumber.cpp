LL qpow(LL a, int n) {
    LL res = 1;
    while (n) {
        if (n & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        n >>= 1;
    }
    return res;
}
LL inv[maxn], fac[maxn], invf[maxn], B[maxn];
inline LL C(LL x, LL y) {
    return ((fac[x] * invf[y]) % MOD * invf[x - y]) % MOD;
}
inline LL pow_sum(int m, int n){
    LL res = 0;
    for (int i = 0; i <= n; i++) res = (res + C(n + 1, i) * B[i] % MOD * qpow(m, n + 1 - i)) % MOD;
    res = (res * inv[n + 1]) % MOD;
    return res;
}
void init(){
    invf[0] = inv[0] = inv[1] = fac[0] = fac[1] = 1;
    for (LL i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % MOD;
    for (int i = 2; i < maxn; i++) inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 1; i < maxn; i++) invf[i] = invf[i - 1] * inv[i] % MOD;
    B[0] = 1;
    for (int i = 1; i < maxn; i++) {
        B[i] = 0;
        for(int j = 0; j < i; j++) B[i] = (B[i] + C(i + 1, j) * B[j]) % MOD;
        B[i] = ((B[i] * -inv[i + 1]) % MOD + MOD) % MOD;
    }
    B[1] = (MOD - B[1]) % MOD;
}
