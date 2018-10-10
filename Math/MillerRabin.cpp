const int S = 20;
LL N, M, T;
LL qpow(__int128 a, LL n, __int128 wm) {
    __int128 r = 1;
    while (n) {
        if (n & 1) r = r * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return LL(r);
}
//composite : true
bool check(LL a, LL n, LL x, LL t) {
    LL ret = qpow(a, x, n);
    LL last = ret;
    for (int i = 1; i <= t; i++) {
        ret = qpow(ret, 2, n);
        if (ret == 1 && last != 1 && last != n - 1) return true; //合数
        last = ret;
    }
    if (ret != 1) return true;
    return false;
}
// Miller_Rabin()
bool Miller_Rabin(LL n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if ((n & 1) == 0) return false; //偶数
    LL x = n - 1;
    LL t = 0;
    while ((x & 1) == 0) {x >>= 1; t++;}
    for (int i = 0; i < S; i++) {
        LL a = rand() % (n - 1) + 1;
        if (check(a, n, x, t)) return false;//合数
    }
    return true;
}

//pollard_rho
LL factor[100];
int tol;
LL Pollard_rho(LL x, LL c) {
    LL i = 1, k = 2;
    LL x0 = rand() % x;
    LL y = x0;
    while (1) {
        i++;
        x0 = (qpow(x0, 2, x) + c) % x;
        LL d = abs(__gcd(y - x0, x));
        if (d != 1 && d != x) return d;
        if (y == x0) return x;
        if (i == k) {y = x0; k += k;}
    }
}
void fac(LL n) {
    if (Miller_Rabin(n)) {
        factor[tol++] = n;
        return;
    }
    LL p = n;
    while (p >= n) p = Pollard_rho(p, rand() % (n - 1) + 1);
    fac(p);
    fac(n / p);
}
int main() {
    srand(time(NULL));
    cin >> T;
    while (T--) {
        cin >> N;
        tol = 0;
        fac(N);
        sort(factor, factor + tol);
        if (Miller_Rabin(N)) printf("Prime\n");
        else printf("%lld\n", factor[0]);
    }
    return 0;
}
