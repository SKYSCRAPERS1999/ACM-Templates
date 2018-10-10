const int maxn = 1e5 + 11;
int N, M, T;
struct E{
    int u, v, w;
    E(){}
    E(int u, int v, int w):u(u),v(v),w(w){}
};
vector<int> G[maxn];
vector<E> edge;
void addEdge(int u, int v, int w){
    edge.push_back(E(u, v, w));
    edge.push_back(E(v, u, w));
    G[u].push_back(edge.size() - 2);
    G[v].push_back(edge.size() - 1);
}
int ver[maxn], dep[maxn], First[maxn], Dis[maxn]; int cur = -1;
void dfs_rmq(int u = 0, int deep = 0, int pu = -1){
    ver[++cur] = u; First[u] = cur; dep[cur] = deep;
    for (int i = 0; i < G[u].size(); i++){
        E &e = edge[G[u][i]];
        if (e.v != pu){
            Dis[e.v] = Dis[u] + e.w;
            dfs_rmq(e.v, deep + 1, u);
            ver[++cur] = u; dep[cur] = deep;
        }
    }
}
/************Segment Tree*************/
struct Node{
    int L, R;
    int mmin, arg;
}node[maxn<<2];
int inline LC(int i) {return i*2;}
int inline RC(int i) {return i*2+1;}
void build(int L, int R, int i){
    node[i].L = L, node[i].R = R;
    if (L == R){node[i].mmin = dep[L]; node[i].arg = L; return;}
    int M = (L + R) / 2;
    build(L, M, LC(i));
    build(M + 1, R, RC(i));
    if (node[LC(i)].mmin > node[RC(i)].mmin){
        node[i].mmin = node[RC(i)].mmin;
        node[i].arg = node[RC(i)].arg;
    }else{
        node[i].mmin = node[LC(i)].mmin;
        node[i].arg = node[LC(i)].arg;
    }
}
int pos, val;   // 更新位置、數值大小
void update(int L, int R, int i){
    if (L == R){node[i].mmin = val; node[i].arg = L; return;}
    int M = (L + R) / 2;
    if (pos <= M) update(L, M, LC(i));
    if (pos > M) update(M + 1, R, RC(i));
    if (node[LC(i)].mmin > node[RC(i)].mmin){
        node[i].mmin = node[RC(i)].mmin;
        node[i].arg = node[RC(i)].arg;
    }else{
        node[i].mmin = node[LC(i)].mmin;
        node[i].arg = node[LC(i)].arg;
    }
}
int x1, x2, res, arg;  // 查詢範圍[x1,x2]並且累計總和
void query(int L, int R, int i){
    if (x1 <= L && R <= x2){
        if (res > node[i].mmin) res = node[i].mmin, arg = node[i].arg;
        return;
    }
    int M = (L + R) / 2;
    if (x1 <= M) query(L, M, LC(i));
    if (x2 > M) query(M + 1, R, RC(i));
}
/****************************************/
// Get index of the minimum depth, instead of the minimum height.
int lca_rmq(int u, int v){
    u = First[u], v = First[v];
    if (u > v) swap(u, v);
    x1 = u, x2 = v, res = INF, arg = u;
    query(0, cur, 1);
    return ver[arg];
}
int dis_rmq(int u, int v){
    return Dis[u] + Dis[v] - 2 * Dis[lca_rmq(u, v)];
}
void init_rmq(){
    dfs_rmq(); build(0, cur, 1);
}
