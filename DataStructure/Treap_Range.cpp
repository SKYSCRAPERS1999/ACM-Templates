#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&(-(x)))
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int maxn = 1e5 + 11;
int N, M, T, root, tot;
int sz[maxn], ch[maxn][2], rnd[maxn], val[maxn];
bool lazy[maxn];
inline int read() {
    int num = 0; char c; bool flag = false;
    while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
    if (c == '-') flag = true;
    else num = c - '0';
    while (isdigit(c = getchar())) num = num * 10 + c - '0';
    return (flag ? -1 : 1) * num;
}
inline int newNode(int x) {
    sz[++tot] = 1; val[tot] = x;
    rnd[tot] = rand();
    return tot;
}
inline void Update(int x) {
    sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
}
inline void pushDown(int x) {
    if (x && lazy[x]) {
        swap(ch[x][0], ch[x][1]);
        if (ch[x][0]) lazy[ch[x][0]] ^= 1;
        if (ch[x][1]) lazy[ch[x][1]] ^= 1;
        lazy[x] = 0;
    }
}
void Split(int now, int k, int &x, int &y) {
    if (!now) { x = y = 0; return; }
    pushDown(now); // <= to left, > to right
    if (sz[ch[now][0]] + 1 <= k) x = now, Split(ch[now][1], k - sz[ch[now][0]] - 1, ch[now][1], y);
    else y = now, Split(ch[now][0], k, x, ch[now][0]);
    Update(now);
}
int Merge(int x, int y) {
    if (!x || !y) return x + y;
    if (rnd[x] < rnd[y]) {
        pushDown(x);
        ch[x][1] = Merge(ch[x][1], y);
        Update(x);
        return x;
    } else {
        pushDown(y);
        ch[y][0] = Merge(x, ch[y][0]);
        Update(y);
        return y;
    }
}
void Reverse(int l, int r) {
    int x, y, z;
    Split(root, r, x, z);
    Split(x, l - 1, x, y);
    lazy[y] ^= 1;
    root = Merge(Merge(x, y), z);
}
vector<int> ans;
void dfs(int now) {
    pushDown(now);
    if (ch[now][0]) dfs(ch[now][0]);
    if (val[now] >= 1 && val[now] <= N) ans.push_back(val[now]);
    if (ch[now][1]) dfs(ch[now][1]);
}
int build(int L = 1, int R = N) {
    if (L > R) return 0;
    int M = (L + R) / 2;
    int now = newNode(M);
    ch[now][0] = build(L, M - 1);
    ch[now][1] = build(M + 1, R);
    Update(now);
    return now;
}
int main() {
    srand(time(NULL));
    N = read(); M = read();
    root = build();
    for (int i = 1, l, r; i <= M; i++) {
        l = read(); r = read();
        Reverse(l, r);
    }
    dfs(root);
    for (int i = 0; i < ans.size(); i++) printf("%d%c", ans[i], " \n"[i==ans.size()-1]);
}
/*
5 3
1 3
1 3
1 4

*/


