const int INF = 0x3f3f3f3f;
const int maxn = 1000 + 11;
int N, M, T, P, Q;
int kase = 0;
struct E {
    int u, v, cap, flow;
    E(){}
    E(int u, int v, int cap, int flow):u(u),v(v),cap(cap),flow(flow){}
};
vector<E> edge;
vector<int> G[maxn];
int Index[maxn], pi[maxn], btn[maxn]; bool vis[maxn];
int BFS(int s, int t){
    memset(vis, 0, sizeof(vis));
    memset(pi, -1, sizeof(pi));
    memset(btn, 0x3f, sizeof(btn));
    queue<int> Q; Q.push(s); pi[s] = s;
    while (!Q.empty()){
        int u = Q.front(); Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = 0; i < G[u].size(); i++){
            E &e = edge[G[u][i]];
            if (!vis[e.v] && e.cap > 0){
                btn[e.v] = min(btn[u], e.cap);
                Index[e.v] = G[u][i];
                pi[e.v] = u; Q.push(e.v);
                if (e.v == t) return btn[t];
            }
        }
    }
    return 0;
}
int MF(int s, int t) {
    int F, dF;
    for (F = 0; (dF = BFS(s, t)) > 0; F += dF) {
        for (int i = t; i != s; i = pi[i]){
            int ind = Index[i];
            edge[ind].cap -= dF; edge[ind].flow += dF;
            edge[ind^1].cap += dF;
        }
    }
    return F;
}
void addEdge(int u, int v, int cap) {
    edge.push_back(E(u, v, cap, 0));
    edge.push_back(E(v, u, 0, 0));
    G[u].push_back(edge.size() - 2);
    G[v].push_back(edge.size() - 1);
}
