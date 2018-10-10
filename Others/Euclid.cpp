LL similar_euclid(LL a, LL c, LL b, LL n) {
    if(!a) return (b / c) * (n + 1) % MOD;
    if(a >= c) return ((__int128)(a / c) % MOD * (__int128)n * (n + 1) / 2 % MOD + similar_euclid(a % c, c, b, n)) % MOD;
    if(b >= c) return ((__int128)(b / c) * (__int128)(n + 1) % MOD + similar_euclid(a, c, b % c, n)) % MOD;
    LL m = ((__int128)a * n + b) / c;
    return ((__int128)n * m % MOD - similar_euclid(c, a, c - b - 1, m - 1) + MOD) % MOD;
}
