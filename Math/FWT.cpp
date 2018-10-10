#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
const int N = 19;
const int MOD = 998244353;

inline int add(int x) {
    return x >= MOD ? x - MOD : x;
}
inline int sub(int x) {
    return x < 0 ? x + MOD : x;
}
inline int mul(int x, int y) {
    return (long long) x * y % MOD;
}
inline int pwr(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x)) {
        if (y & 1) ans = mul(ans, x);
    }
    return ans;
}

int n;
int a[maxn];
int cnt[1 << N | 10], sum;
void fwt(int a[], int b = 0) {
    int inv = (MOD + 1) / 2;
    for (int d = 1; d < (1 << N); d <<= 1)
        for (int m = d << 1, i = 0; i < (1 << N); i += m)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = x + y;
                if (a[i + j] >= MOD) a[i + j] -= MOD;
                a[i + j + d] = x - y + MOD;
                if (a[i + j + d] >= MOD) a[i + j + d] -= MOD;
                if (b) {
                    // Do many FWT once
                    a[i + j] = mul(a[i + j], inv);
                    a[i + j + d] = mul(a[i + j + d], inv);
                }
            }
}

bool check(int x) {
    static int f[1 << N | 10];
    for (int i = 0; i < (1 << N); i++) {
        // Do many FWT once
        f[i] = pwr(cnt[i], x);
    }
    fwt(f, 1);
    return f[sum];
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) {
        scanf("%d", a + i);
        sum ^= a[i];
        cnt[a[i]] = 1;
    }
    cnt[0] = 1;
    fwt(cnt);
    if (sum == 0) {
        printf("%d\n", n);
    }
    else {
        int l = 1, r = min(20, n), ans = r;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                ans = mid;
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        printf("%d\n", n - ans);
    }
}

