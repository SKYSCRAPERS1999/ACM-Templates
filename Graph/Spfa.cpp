//Spfa is BellmanFord with queue acceleration.(Like BFS)
const int maxn = 1000 + 11;
int N, M, T;
struct E {
    int u, v, w;
    E() {}
    E(int u, int v, int w):u(u),v(v),w(w){}
};
vector<E> edge;
vector<int> G[maxn];
int d[maxn]; bool vis[maxn];
void Spfa(int s){
    memset(vis, 0, sizeof(vis));
    memset(d, 0x3f, sizeof(d));
    queue<int> Q; Q.push(s);
    d[s] = 0; vis[s] = 1;
    while (!Q.empty()){
        int u = Q.front(); Q.pop(); vis[u] = 0;
        for (int i = 0; i < G[u].size(); i++){
            E &e = edge[G[u][i]];
            if (d[e.v] > d[u] + e.w) {
                d[e.v] = d[u] + e.w;
                if (!vis[e.v]) {
                    vis[e.v] = 1;
                    Q.push(e.v);
                }
            }
        }
    }
}
