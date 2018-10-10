const int maxn = 1e5 + 11;
int idg[maxn], q[maxn], qn; //idg is in-degree
//Return 0 if there is a cycle
bool topoSort(){
    qn = 0;
    for (int u = 0; u < N; u++) if (!idg[u]) q[qn++] = u;
    for (int i = 0; i < qn; i++){
        int u = q[i];
        for (int v : G[u]){
            idg[v]--;
            if (idg[v] == 0) q[qn++] = v;
        }
    }
    return qn == N;
}
