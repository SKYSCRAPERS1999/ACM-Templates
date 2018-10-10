const int maxn = 1000 + 1000;
int N, M, T;
vector<int> G[maxn];
int mx[maxn], my[maxn], vis[maxn];
bool DFS(int ux){
    vis[ux] = 1;
    for (int i = 0; i < G[ux].size(); i++){
        int uy = G[ux][i];
        if (vis[uy]) continue;
        vis[uy] = 1;
        if (my[uy] == -1 || DFS(my[uy])){
            mx[ux] = uy;
            my[uy] = ux;
            return true;
        }
    }
    return false;
}
int BiMatch(){
    int cnt = 0; memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    for (int ux = 0; ux < N; ux++) {
        if (mx[ux] != -1) continue;
        memset(vis, 0, sizeof(vis));
        if (DFS(ux)) cnt++;
    }
    return cnt;
}
