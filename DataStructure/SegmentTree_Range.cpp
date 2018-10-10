// to replace or to modify!
#define LC(i) ((i)*2)
#define RC(i) ((i)*2+1)
const int maxn = 1e5 + 11;
int N, M, T;
int a[maxn];
int sum[maxn << 2], lazy[maxn << 2];
void build(int L, int R, int o = 1) {
    lazy[o] = 0;
    if (L == R) { sum[o] = a[L]; return; }
    int M = (L + R) >> 1;
    build(L, M, LC(o));
    build(M + 1, R, RC(o));
    sum[o] = sum[LC(o)] + sum[RC(o)];
}
inline void pushdown(int L, int M, int R, int o) {
    lazy[LC(o)] += lazy[o]; lazy[RC(o)] += lazy[o];
    sum[LC(o)] += (M - L + 1) * lazy[o]; sum[RC(o)] += (R - M) * lazy[o];
    lazy[o] = 0;
}
void update(int x1, int x2, int val, int L = 1, int R = N, int o = 1) {
    if (x1 <= L && R <= x2) {sum[o] += val * (R - L + 1); lazy[o] += val; return;}
    int M = (L + R) >> 1;
    if (lazy[o]) pushdown(L, M, R, o);
    if (x1 <= M) update(x1, x2, val, L, M, LC(o));
    if (x2 > M) update(x1, x2, val, M + 1, R, RC(o));
    sum[o] = sum[LC(o)] + sum[RC(o)];
}
int query(int x1, int x2, int L = 1, int R = N, int o = 1) {
    if (x1 <= L && R <= x2) return sum[o];
    int res = 0, M = (L + R) >> 1;
    if (lazy[o]) pushdown(L, M, R, o);
    if (x1 <= M) res += query(x1, x2, L, M, LC(o));
    if (x2 > M) res += query(x1, x2, M + 1, R, RC(o));
    return res;
}
