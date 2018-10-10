#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&(-(x)))
#define MP make_pair
#define fi first
#define se second
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); //mt19937_64 for 64-bits
bool Finish_read;
template<class T>inline void read(T &x) {Finish_read = 0; x = 0; int f = 1; char ch = getchar(); while(!isdigit(ch)) {if(ch == '-')f = -1; if(ch == EOF)return; ch = getchar();} while(isdigit(ch))x = x * 10 + ch - '0', ch = getchar(); x *= f; Finish_read = 1;}
typedef unsigned long long LL;
typedef pair<int,int> pii;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int maxn = 2e5 + 11;

#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
LL sum[maxn<<2],add[maxn<<2],mul[maxn<<2];
void build(int o,int l,int r) {
	add[o]=0,mul[o]=1;
	if (l==r) {sum[o]=0;return;}
	int mid=l+r>>1;
	build(lson);
	build(rson);
	sum[o]=sum[o<<1]+sum[o<<1|1];
}
inline void pushdown(int o,int len) {
	int lf=len-(len>>1),rg=len>>1;
	if (mul[o]^1) {
		add[o<<1]*=mul[o],mul[o<<1]*=mul[o],sum[o<<1]*=mul[o];
		add[o<<1|1]*=mul[o],mul[o<<1|1]*=mul[o],sum[o<<1|1]*=mul[o];
		mul[o]=1;
	}
	if (add[o]) {
		add[o<<1]+=add[o],sum[o<<1]+=lf*add[o];
		add[o<<1|1]+=add[o],sum[o<<1|1]+=rg*add[o];
		add[o]=0;
	}
}
void update(int o,int l,int r,int L,int R,LL v,int opt) {
	if (L<=l&&r<=R) {
		if (opt&1) add[o]*=v,mul[o]*=v,sum[o]*=v;
		else add[o]+=v,sum[o]+=(r-l+1)*v;
		return;
	}
	pushdown(o,r-l+1);
	int mid=l+r>>1;
	if (L<=mid) update(lson,L,R,v,opt);
	if (mid<R) update(rson,L,R,v,opt);
	sum[o]=sum[o<<1]+sum[o<<1|1];
}
LL query(int o,int l,int r,int L,int R) {
	if (L<=l&&r<=R) return sum[o];
	pushdown(o,r-l+1);
	int mid=l+r>>1;
	LL ret=0;
	if (L<=mid) ret+=query(lson,L,R);
	if (mid<R) ret+=query(rson,L,R);
	return ret;
}

int N, M, Q, T, tot;
int p[maxn], dep[maxn], ver[maxn<<1], id[maxn], top[maxn], sz[maxn], son[maxn];
vector<int> G[maxn];
void dfs1(int u = 1, int pu = 1, int d = 0){
    p[u] = pu; dep[u] = d; sz[u] = 1;
    int mx = 0;
    for (int v : G[u]){
        if (v != pu){
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > mx) mx = sz[v], son[u] = v;
        }
    }
}
void dfs2(int u = 1, int s = 1){
    id[u] = ++tot; ver[tot] = u; top[u] = s;
    if (son[u]) dfs2(son[u], s);
    for (int v : G[u]){
        if (v != p[u] && v != son[u]){
            dfs2(v, v);
        }
    }
}
LL Query_Sum(int u, int v){
    int fu = top[u], fv = top[v]; LL ret = 0;
    while (fu != fv){
        if (dep[fu] < dep[fv]) swap(fu, fv), swap(u, v);
        ret += query(1, 1, tot, id[fu], id[u]);
        u = p[fu], fu = top[u];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ret += query(1, 1, tot, id[v], id[u]);
    return ret;
}
void Update(int u, int v, LL val, int opt){
    int fu = top[u], fv = top[v];
    while (fu != fv){
        if (dep[fu] < dep[fv]) swap(fu, fv), swap(u, v);
        update(1, 1, tot, id[fu], id[u], val, opt);
        u = p[fu], fu = top[u];
    }
    if (dep[u] < dep[v]) swap(u, v);
    update(1, 1, tot, id[v], id[u], val, opt);
}

int main(){
    while (scanf("%d", &N) != EOF) {
        tot = 0;
        memset(son, 0, sizeof(int)*(N+11));
        for (int i = 1; i <= N; i++) G[i].clear();
        for (int i = 2, fa; i <= N; i++){
            scanf("%d", &fa);
            G[fa].push_back(i);
        }
        dfs1(); dfs2();
        build(1, 1, tot);
        cin >> Q;
        int op, u, v; LL x;
        while (Q--){
            scanf("%d%d%d", &op, &u, &v);
            if (op == 1){
                scanf("%llu", &x);
                Update(u, v, x, 1);
            }else if (op == 2){
                scanf("%llu", &x);
                Update(u, v, x, 2);
            }else if (op == 3){
                Update(u, v, 1LL * -1, 1);
                Update(u, v, 1LL * -1, 2);
            }else{
                LL res = Query_Sum(u, v);
                printf("%llu\n", res);
            }
        }
    }
    return 0;
}

/*
7
1 1 1 2 2 4
5
2 5 6 1
1 1 6 2
4 5 6
3 5 2
4 2 2
2
1
4
3 1 2
4 1 2
3 1 1
4 1 1
7
1 1 1 2 2 4
5
2 5 6 1
1 1 6 2
4 5 6
3 5 2
4 2 2
2
1
4
3 1 2
4 1 2
3 1 1
4 1 1

*/

