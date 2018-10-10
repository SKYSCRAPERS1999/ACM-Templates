const int maxn = 1000 + 11;
int N, M, T;
int pi[maxn], Index[maxn], d[maxn]; bool vis[maxn];
struct E{
    int u, v, cap, flow, cost;
    E(){}
    E(int u, int v, int cap, int flow, int cost):u(u),v(v),cap(cap),flow(flow),cost(cost){}
};
vector<E> edge;
vector<int> G[maxn];
int Spfa(int s, int t){
    memset(vis, 0, sizeof(vis)); memset(d, 0x3f, sizeof(d));
    queue<int> Q; pi[s] = s; vis[s] = 1; d[s] = 0; Q.push(s);
    while(!Q.empty()){
        int u = Q.front(); Q.pop(); vis[u] = 0;
        for (int i = 0; i < G[u].size(); i++){
            E &e = edge[G[u][i]];
            if (e.cap > 0 && d[e.v] > d[u] + e.cost){
                pi[e.v] = u; Index[e.v] = G[u][i];
                d[e.v] = d[u] + e.cost;
                if (!vis[e.v]){
                    Q.push(e.v); vis[e.v] = 1;
                }
            }
        }
    }
    if (d[t] == INF) return 0;
    int dF = INF;
    for (int i = t; i != s; i = pi[i])  dF = min(dF, edge[Index[i]].cap);
    return dF;
}
int MCMF(int s, int t){
    int F, dF, Cost;
    for (F = 0, Cost = 0; (dF = Spfa(s, t)) > 0; F += dF, Cost += dF * d[t]){
        for (int j = t; j != s; j = pi[j]){
            int ind = Index[j];
            edge[ind].flow += dF; edge[ind].cap -= dF;
            edge[ind^1].cap += dF;
        }
    }
    return Cost;
}
void addEdge(int u, int v, int cap, int cost){
    edge.push_back(E(u, v, cap, 0, cost));
    edge.push_back(E(v, u, 0, 0, -cost));
    G[u].push_back(edge.size() - 2);
    G[v].push_back(edge.size() - 1);
}
