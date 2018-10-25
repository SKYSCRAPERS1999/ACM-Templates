#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 1e7 + 5e6;
int N, Q, M, tot, rt;
int lson[maxn], rson[maxn], sum[maxn], lazy[maxn];
int x1, x2, val;
void update(int L, int R, int& i) {
    if (!i) { i = ++tot; }
    if (x1 <= L && R <= x2) {sum[i] = val * (R - L + 1); lazy[i] = val; return;}
    int M = (L + R) / 2;
    if (lazy[i] != -1) {
        if (L != R){
            if (!lson[i]) { lson[i] = ++tot; }
            if (!rson[i]) { rson[i] = ++tot; }
            lazy[lson[i]] = lazy[rson[i]] = lazy[i];
            sum[lson[i]] = (M - L + 1) * lazy[i];
            sum[rson[i]] = (R - M) * lazy[i];
        }
        lazy[i] = -1;
    }
    if (x1 <= M) { update(L, M, lson[i]); }
    if (x2 > M) { update(M + 1, R, rson[i]); }
    sum[i] = sum[lson[i]] + sum[rson[i]];
}

int res;
void query(int L, int R, int& i) {
    if (x1 <= L && R <= x2) {res += sum[i]; return;}
    int M = (L + R) / 2;
    if (lazy[i] != -1) {
        if (!lson[i]) { lson[i] = ++tot; }
        if (!rson[i]) { rson[i] = ++tot; }
        lazy[lson[i]] = lazy[rson[i]] = lazy[i];
        sum[lson[i]] = (M - L + 1) * lazy[i];
        sum[rson[i]] = (R - M) * lazy[i];

        lazy[i] = -1;
    }
    if (x1 <= M) { query(L, M, lson[i]); }
    if (x2 > M) { query(M + 1, R, rson[i]); }
}

int main() {
    cin >> N >> Q;
    int l, r, k;
    memset(lazy, -1, sizeof(lazy));
    while (Q--) {
        scanf("%d%d%d", &l, &r, &k);
        x1 = l, x2 = r, val = 2 - k;
        update(1, N, rt);
        printf("%d\n", N - sum[1]);
    }
    return 0;
}

