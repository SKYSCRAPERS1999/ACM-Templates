struct Trie{
    int ch[maxn][maxc];
    int val[maxn];
    int sz;
    Trie(){sz = 1; clr(ch[0]); val[0] = 1;}
    int idx(char c) {return c - 'a';}
    void add(char* s, int v){
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; i++){
            int c = idx(s[i]);
            if (!ch[u][c]){
                clr(ch[sz]);
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }
    void dfs(int u = 0, int dep = 0){
        for (int i = 0; i < maxc; i++){
            int v = ch[u][i];
            if (v) dfs(v, dep + 1);
        }
    }
}trie;
