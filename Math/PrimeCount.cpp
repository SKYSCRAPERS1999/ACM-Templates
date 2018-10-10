#include<bits/stdc++.h>
#define MAXN 1000005// MAXN=sqrt(upper_bound)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
LL f[MAXN], g[MAXN], n, k; //f[i]:pi(n/i),g[i]:pi(i)
// PrimeCount: g(n,j) = g(n,j−1) − (1) * [g([n/Pj],j−1)−g(Pj−1,j−1)] iff n is prime
// PrimeSum: g(n,j) = g(n,j−1) − (n) * [g([n/Pj],j−1)−g(Pj−1,j−1)] iff n is prime
// the i-th iteration (2<=i<=m) is according to g(:,i-1) -> g(:,i)
// f is used to save space

LL PrimeCount(LL n) {
    LL i, j, m = 0;
    for (m = 1; m * m <= n; m++) f[m] = n / m - 1;
    for (i = 2; i <= m; i++) g[i] = i - 1;
    for (i = 2; i <= m; i++) {
        if (g[i] == g[i - 1]) continue;
        for (j = 1; j <= min(m - 1, n / i / i); ++j) {
            if (i * j < m) f[j] -= f[i * j] - g[i - 1];
            else f[j] -= g[n / i / j] - g[i - 1];
        }
        for (j = m; j >= i * i; j--) g[j] -= g[j / i] - g[i - 1];
    }
    return f[1];
}

// Be caution that it may cause long long overflow.
LL f[maxn], g[maxn];
inline LL C2(LL x) {
    if (x >= MOD) x %= MOD;
    return x * (x - 1) / 2;
}
LL PrimeSum(LL n) {
    LL i, j, m = 0;
    for (m = 1; m * m <= n; m++) f[m] = (C2(n / m + 1) - 1 + MOD) % MOD;
    for (i = 2; i <= m; i++) g[i] = (C2(i + 1) - 1 + MOD) % MOD;
    for (i = 2; i <= m; i++) {
        if (g[i] == g[i - 1]) continue;
        for (j = 1; j <= min(m - 1, n / i / i); ++j) {
            if (i * j < m) f[j] -= (__int128)i * (f[i * j] - g[i - 1] + MOD) % MOD;
            else f[j] -= (__int128)i * (g[n / i / j] - g[i - 1] + MOD) % MOD;
            f[j] = (f[j] % MOD + MOD) % MOD;
        }
        for (j = m; j >= i * i; j--) {
            g[j] -= (__int128)i * (g[j / i] - g[i - 1] + MOD) % MOD;
            g[j] = (g[j] % MOD + MOD) % MOD;
        }
    }
    return f[1];
}


int main() {
    while(scanf("%lld", &n) == 1) {
        printf("%lld\n", PrimeSum(n));
        printf("%lld\n", PrimeCount(n));
    }
    return 0;
}


