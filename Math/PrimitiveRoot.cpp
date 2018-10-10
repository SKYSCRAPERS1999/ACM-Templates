#include<bits/stdc++.h>
const int maxn = 1e6 + 11;
using namespace std;
typedef long long LL;
vector<LL> a;
LL pow_mod(LL a, LL i, LL mod) {
    if (i == 0) return 1;
    LL s = 1;
    while(i > 0) {
        if (i & 1) s = (s * a) % mod;
        a = (a * a) % mod;
        i >>= 1;
    }
    return s;
}
bool g_test(LL g, LL p) {
    for (LL i = 0; i < a.size(); i++) if (pow_mod(g, (p - 1) / a[i], p) == 1) return 0;
    return 1;
}
LL primitive_root(LL p) {
    LL tmp = p - 1;
    for (LL i = 2; i <= tmp / i; i++)
        if (tmp % i == 0) {
            a.push_back(i);
            while(tmp % i == 0) tmp /= i;
        }
    if (tmp != 1) a.push_back(tmp);
    LL g = 1;
    while(true) {
        if (g_test(g, p)) return g;
        ++g;
    }
}
int main() {
    LL n;
    while(scanf("%lld", &n) == 1) printf("%lld\n", primitive_root(n));
    return 0;
}

