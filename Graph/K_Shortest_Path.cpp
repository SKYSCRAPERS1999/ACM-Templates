const int INF = 0x3f3f3f3f;
const int maxn = 1000 + 11;
int N, M, T, S, E, K;
struct Edge{int v, w;};
vector<Edge> G[maxn], rG[maxn];
int d[maxn]; bitset<maxn> vis;
struct D {
    int g, u;
    bool operator < (const D &rhs) const {
        return !(g + d[u] < rhs.g + d[rhs.u]);
    }
};
void Dijkstra(int s) {
    memset(d, 0x3f, sizeof(d));
    priority_queue<pii> Q; d[s] = 0;
    Q.push({0, s});
    while (!Q.empty()) {
        int u = Q.top().se;
        Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto e : rG[u]) {
            if (d[e.v] > d[u] + e.w) {
                d[e.v] = d[u] + e.w;
                Q.push({ -d[e.v], e.v});
            }
        }
    }
}
int Astar(int s, int t, int k) {
    if (d[s] == INF) return -1;
    int cnt = 0;
    priority_queue<D> Q;
    Q.push(D{0, s});
    while (!Q.empty()) {
        D cur = Q.top();
        Q.pop();
        if (cur.u == t && ++cnt == k) return cur.g;
        for (auto e : G[cur.u]) {
            Q.push(D{cur.g + e.w, e.v});
        }
    }
    return -1;
}

int main() {
    while (scanf("%d%d",&N,&M)!=EOF){
        scanf("%d%d%d%d",&S,&E,&K,&T);
        for(int i=0;i<=N;i++)G[i].clear(),rG[i].clear();
        vis.reset();
        for(int i=0,u,v,w;i<M;i++){
            scanf("%d%d%d",&u,&v,&w);
            G[u].push_back({v, w});
            rG[v].push_back({u, w});
        }
        Dijkstra(E);
        int ans = Astar(S, E, K);
        if (ans != -1 && ans <= T) puts("yareyaredawa");
        else puts("Whitesnake!");
    }
    return 0;
}
/*
2 2
1 2 2 14
1 2 5
2 1 4

2 1
1 2 2 14
1 2 5
*/

