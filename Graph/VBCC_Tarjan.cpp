const int maxn = 1e5 + 11;
int N, M, T;
vector<pair<int,int> > edge;
vector<int> G[maxn];
vector<int> ebcc[maxn], vbcc[maxn];
stack<pair<int,int> > stk;
map<pair<int,int>, int> eid;
int low[maxn], idx[maxn], ID[maxn]; bool iscut[maxn];
int cnt, id;
void Tarjan(int u, int pu) {
    idx[u] = ++cnt; low[u] = cnt;
    int child = 0;
    for (int i = 0; i < G[u].size(); i++){
        int v = G[u][i];
        if (idx[v] == -1){
            stk.push({u, v}); child++;
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= idx[u]){
                iscut[u] = 1;
                pair<int,int> t;
                do{
                    t = stk.top(); stk.pop();
                    ebcc[id].push_back(eid[t]);
                    if (ID[t.first] != id) vbcc[id].push_back(t.first), ID[t.first] = id;
                    if (ID[t.second] != id) vbcc[id].push_back(t.second), ID[t.second] = id;
                }while (t.first != u || t.second != v);
                id++;
            }
        }else if (idx[v] < idx[u] && v != pu){
            stk.push({u, v});
            low[u] = min(low[u], idx[v]);
        }
    }
    if(pu < 0 && child == 1) iscut[u] = 0;
}
void solve() {
    memset(idx, -1, sizeof(idx)); memset(low, -1, sizeof(low)); memset(iscut, 0, sizeof(iscut)); memset(ID, -1, sizeof(ID));
    cnt = id = 0;
    for (int i = 1; i <= N; i++) {
        if (idx[i] == -1) Tarjan(i, -1);
    }
}
