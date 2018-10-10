const int maxn = 1e5 + 11;
int N, Q, T;
int p[maxn], dep[maxn], ver[maxn<<1], id[maxn], top[maxn], sz[maxn], son[maxn], a[maxn];
vector<int> G[maxn];
void dfs1(int u = 1, int pu = 1, int d = 0){
    p[u] = pu; dep[u] = d; sz[u] = 1;
    int mx = 0;
    for (int v : G[u]){
        if (v != pu){
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > mx) mx = sz[v], son[u] = v;
        }
    }
}
int tot;
void dfs2(int u = 1, int s = 1){
    id[u] = ++tot; ver[tot] = u; top[u] = s;
    if (son[u]) dfs2(son[u], s);
    for (int v : G[u]){
        if (v != p[u] && v != son[u]){
            dfs2(v, v);
        }
    }
}
int mx[maxn<<2], sum[maxn<<2];
void build(int L, int R, int o = 1) {
    if (L == R) { sum[o] = mx[o] = a[ver[L]]; return; }
    int M = (L + R) >> 1;
    build(L, M, LC(o));
    build(M + 1, R, RC(o));
    sum[o] = sum[LC(o)] + sum[RC(o)];
    mx[o] = max(mx[LC(o)], mx[RC(o)]);
}
int query_sum(int x1, int x2, int L = 1, int R = tot, int o = 1) {
    int res = 0;
    if (x1 <= L && R <= x2) return sum[o];
    int M = (L + R) >> 1;
    if (x1 <= M) res += query_sum(x1, x2, L, M, LC(o));
    if (x2 > M) res += query_sum(x1, x2, M + 1, R, RC(o));
    return res;
}
int query_max(int x1, int x2, int L = 1, int R = tot, int o = 1) {
    int res = -INF;
    if (x1 <= L && R <= x2) return mx[o];
    int M = (L + R) >> 1;
    if (x1 <= M) res = max(res, query_max(x1, x2, L, M, LC(o)));
    if (x2 > M) res = max(res, query_max(x1, x2, M + 1, R, RC(o)));
    return res;
}
int Query_Max(int u, int v){
    int fu = top[u], fv = top[v], ret = -INF;
    while (fu != fv){
        if (dep[fu] < dep[fv]) swap(fu, fv), swap(u, v);
        ret = max(ret, query_max(id[fu], id[u]));
        u = p[fu], fu = top[u];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ret = max(ret, query_max(id[v], id[u]));
    return ret;
}
int Query_Sum(int u, int v){
    int fu = top[u], fv = top[v], ret = 0;
    while (fu != fv){
        if (dep[fu] < dep[fv]) swap(fu, fv), swap(u, v);
        ret += query_sum(id[fu], id[u]);
        u = p[fu], fu = top[u];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ret += query_sum(id[v], id[u]);
    return ret;
}
void update(int pos, int val, int L = 1, int R = tot, int o = 1) {
    if (L == R) {sum[o] = mx[o] = val; return;}
    int M = (L + R) >> 1;
    if (pos <= M) update(pos, val, L, M, LC(o));
    if (pos > M) update(pos, val, M + 1, R, RC(o));
    mx[o] = max(mx[LC(o)], mx[RC(o)]);
    sum[o] = sum[LC(o)] + sum[RC(o)];
}
int main(){
    cin >> N;
    for (int i = 0, u, v; i < N - 1; i++){
        scanf("%d%d", &u, &v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for (int i = 1; i <= N; i++) scanf("%d", &a[i]);
    dfs1(); dfs2();
    build(1, tot, 1);
    cin >> Q;
    char op[10]; int u, v;
    while (Q--){
        scanf("%s%d%d", op, &u, &v);
        if (op[0] == 'C'){
            update(id[u], v);
        }else if (op[1] == 'M'){
            printf("%d\n", Query_Max(u, v));
        }else{
            printf("%d\n", Query_Sum(u, v));
        }
    }
    return 0;
}
/*
4
1 2
2 3
4 1
4 2 1 3
12
QMAX 3 4
QMAX 3 3
QMAX 3 2
QMAX 2 3
QSUM 3 4
QSUM 2 1
CHANGE 1 5
QMAX 3 4
CHANGE 3 6
QMAX 3 4
QMAX 2 4
QSUM 3 4

*/
