const int maxn = 100000 + 11;
int N, M, T;
vector<int> G[maxn];
stack<int> stk;
bool in[maxn]; int low[maxn], ID[maxn], idx[maxn];
int cnt, id;
void Tarjan(int u){
    idx[u] = ++cnt; low[u] = cnt; in[u] = 1;
    stk.push(u);
    for (int v : G[u]) {
        if (idx[v] == -1){
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in[v]) low[u] = min(low[u], idx[v]);
    }
    if (idx[u] == low[u]) {
        in[u] = 0; ID[u] = id;
        while (stk.top() != u){
            in[stk.top()] = 0;
            ID[stk.top()] = id;
            stk.pop();
        }
        stk.pop(); id++;
    }
}
void solve(){
    memset(in, 0, sizeof(in)); memset(idx, -1, sizeof(idx)); memset(low, -1, sizeof(low));
    cnt = id = 0;
    for (int i = 0; i < N; i++){
        if (idx[i] == -1) Tarjan(i);
    }
}
