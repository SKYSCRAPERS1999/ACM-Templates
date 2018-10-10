const int maxn = 1000 + 11;
int N, M;
struct E {
    int u, v, w;
    E() {}
    E(int u, int v, int w):u(u),v(v),w(w){}
};
vector<E> edge;
vector<int> G[maxn];
int d[maxn];
bool BellmanFord(int s){
    memset(d, 0x3f, sizeof(d));
    d[s] = 0;
    for (int i = 0; i < N; i++){
        bool ok = true;
        for (int u = 0; u < N; u++){
            for (int j = 0; j < G[u].size(); j++){
                E &e = edge[G[u][j]];
                if (d[e.v] > d[u] + e.w) {
                    d[e.v] = d[u] + e.w;
                    ok = false;
                }
            }
        }
        if (ok) return true;
    }
    return false;
}
