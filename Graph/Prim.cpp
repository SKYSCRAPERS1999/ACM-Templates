const int INF = 0x3f3f3f3f;
const int maxn = 100000;
int M, N, T;
struct E {
    int u, v, w;
    E() {}
    E(int u, int v, int w):u(u),v(v),w(w){}
};
vector<E> edge;
vector<int> G[maxn];
struct D{
    int d, x;
    D(){}
    D(int d, int x):d(d), x(x){};
    bool operator < (const D& rhs) const{return d > rhs.d;}
};
vector<D> v;
bool vis[maxn];
int Prim(){
    v.clear();
    for (int i = 0; i < N; i++) v.push_back(D(INF, i));
    v[0].d = 0; int res = 0;
    memset(vis, 0, sizeof(vis));
    priority_queue<D> pq; pq.push(v[0]);
    while (!pq.empty()){
        D uu = pq.top(); pq.pop();
        vis[uu.x] = true, res += uu.d;
        for (int i = 0; i < G[uu.x].size(); i++) {
            E &e = edge[G[uu.x][i]];
            D &vv = v[e.v];
            if (vis[vv.x]) continue;
            if (vv.d > e.w) {
                vv.d = e.w; pq.push(vv);
            }
        }
    }
    return res;
}
