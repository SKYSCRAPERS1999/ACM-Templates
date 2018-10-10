const int maxn = 100000;
int M, N, T;
struct E {
    int u, v, w;
    E() {}
    E(int u, int v, int w):u(u),v(v),w(w) {}
    bool operator < (const E& rhs) const{
        return w < rhs.w;
    }
};
vector<E> edge;
int p[maxn];
void init() {for (int i = 0; i < N; i++) p[i] = i;}
int pfind(int x) {
    if (p[x] == x) return x;
    return p[x] = pfind(p[x]);
}
int kruskal() {
    init();
    sort(edge.begin(), edge.end());
    int ans = 0;
    for (int i = 0; i < edge.size(); i++) {
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        int pu = pfind(u), pv = pfind(v);
        if (pu != pv) {
            p[pu] = pv; // Very important!!!
            ans += w;
        }
    }
    return ans;
}
