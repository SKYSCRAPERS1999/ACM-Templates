// to replace or to modify!
#define LC(i) ((i)*2)
#define RC(i) ((i)*2+1)
const int maxn = 1e5 + 11;
int sum[maxn<<2], a[maxn];
int N, M, T;
void build(int L = 1, int R = N, int o = 1) {
    if (L == R) {sum[o] = a[L]; return;}
    int M = (L + R) >> 1;
    build(L, M, LC(o));
    build(M + 1, R, RC(o));
    sum[o] = sum[LC(o)] + sum[RC(o)];
}
void update(int pos, int val, int L = 1, int R = N, int o = 1) {
    if (L == R) { sum[o] += val; return; }
    int M = (L + R) >> 1;
    if (pos <= M) update(pos, val, L, M, LC(o));
    if (pos > M) update(pos, val, M + 1, R, RC(o));
    sum[o] = sum[LC(o)] + sum[RC(o)];
}
int query(int x1, int x2, int L = 1, int R = N, int o = 1) {
    if (x1 <= L && R <= x2) return sum[o];
    int res = 0, M = (L + R) >> 1;
    if (x1 <= M) res += query(x1, x2, L, M, LC(o));
    if (x2 > M) res += query(x1, x2, M + 1, R, RC(o));
    return res;
}
