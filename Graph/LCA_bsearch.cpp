const int maxn = 1e5 + 11;
const int maxh = 16;
int N, M, T;
struct E{
    int u, v, w;
};
vector<E> G[maxn];
vector<E> edge;
int p[maxn][maxh], dep[maxn], Dis[maxn];
void dfs(int u, int pu = -1, int d = 0){
    p[u][0] = pu; dep[u] = d;
    for (E e : G[u]){
        if (e.v != pu) {
            Dis[e.v] = Dis[u] + e.w;
            dfs(e.v, u, d + 1);
        }
    }
}
void init(){
    dfs(0);
    for (int i = 0; i + 1 < maxh; i++){
        for (int u = 1; u <= N; u++){
            if (p[u][i] == -1) p[u][i + 1] = -1;
            else p[u][i + 1] = p[p[u][i]][i];
        }
    }
}
int lca(int u, int v){
    if (dep[u] > dep[v]) swap(u, v); // Here u is higher
    int len = abs(dep[u] - dep[v]);
    for (int i = 0; i < maxh; i++) {
        if ((len >> i) & 1) v = p[v][i];
    }
    if (u == v) return u;
    else{
        for (int i = maxh - 1; i >= 0; i--){
            if (p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
        }
        return p[u][0];
    }
}
int dist(int u, int v){
    return Dis[u] + Dis[v] - 2 * Dis[lca(u, v)];
}
