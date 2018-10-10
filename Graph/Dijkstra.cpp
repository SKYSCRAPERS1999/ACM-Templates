const int INF = 0x3f3f3f3f;
const int maxn = 1000 + 11;
int N, M, T;
struct E {
    int u, v, w;
};
vector<E> edge;
vector<int> G[maxn];
struct D{
    int d, x;
    D(){}
    D(int d, int x):d(d),x(x){}
    bool operator < (const D& rhs) const{return d > rhs.d;}
};
int pi[maxn], vis[maxn];
vector<D> v;
void Dijkstra(int s){
    v.clear();
    for (int i = 0;  i < N;  i++) v.push_back(D(INF, i));
    memset(pi, -1, sizeof(pi)); memset(vis, 0, sizeof(vis));
    priority_queue<D> pq; v[s].d = 0; pq.push(v[s]);
    while (!pq.empty()){
        D uu = pq.top(); pq.pop();
        if (vis[uu.x]) continue;
        vis[uu.x] = true;
        for (int i = 0; i < G[uu.x].size(); i++){
            E &e = edge[G[uu.x][i]];
            D &vv = v[e.v];
            if (vis[vv.x]) continue;
            if (vv.d > uu.d + e.w) {
                vv.d = uu.d + e.w;
                pi[vv.x] = uu.x; pq.push(vv);
            }
        }
    }
}
