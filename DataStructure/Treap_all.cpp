// luogu-judger-enable-o2
#pragma GCC optimize(3)
#include<bits/stdc++.h>
inline unsigned RAND() {
    static unsigned x = 123456789;
    static unsigned y = 362436069;
    static unsigned z = 521288629;
    static unsigned w = 88675123;
    unsigned t;
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

inline int max(int x,int y){if (x>y) return x;return y;}
inline int min(int x,int y){if (x<y) return x;return y;}
inline void swap(int &a,int &b){a^=b,b^=a,a^=b;}

typedef long long LL;
typedef unsigned long long ULL;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int maxn = 5e5 + 11;
int N, M, T, a[maxn], root, tot;
int sz[maxn], ch[maxn][2], rnd[maxn], val[maxn], sum[maxn];
int lmx[maxn], rmx[maxn], mx[maxn];
bool lazy_rev[maxn], lazy_mod[maxn];
void readin() {
    srand(19990130);
    std::cin >> N >> M;
    tot = root = 0;
    for (int i = 1; i <= N; i++) scanf("%d", &a[i]);
}
//-fsanitize=undefined

std::queue<int> trashcan;
void trash(int x){
    if (!x) return;
    trashcan.push(x);
    trash(ch[x][0]);
    trash(ch[x][1]);
    sz[x]=ch[x][0]=ch[x][1]=val[x]=sum[x]=lmx[x]=rmx[x]=mx[x]=lazy_mod[x]=lazy_rev[x]=0;
}
inline int newNode(int v) {
    int x = 0;
    if (!trashcan.empty()) x = trashcan.front(), trashcan.pop();
    else x = ++tot;
    sz[x] = 1; rnd[x] = rand();
    sum[x] = val[x] = v;
    lmx[x] = rmx[x] = max(v, 0);
    mx[x] = v;
    return x;
}
inline void Update(int x) {
    if (ch[x][0] && ch[x][1]) {
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
        sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
        mx[x] = max(mx[ch[x][0]], mx[ch[x][1]]);
        mx[x] = max(mx[x], rmx[ch[x][0]] + val[x] + lmx[ch[x][1]]);
        lmx[x] = max(lmx[ch[x][0]], sum[ch[x][0]] + val[x] + lmx[ch[x][1]]);
        rmx[x] = max(rmx[ch[x][1]], sum[ch[x][1]] + val[x] + rmx[ch[x][0]]);
    } else if (ch[x][0]) {
        sz[x] = sz[ch[x][0]] + 1;
        sum[x] = sum[ch[x][0]] + val[x];
        mx[x] = max(mx[ch[x][0]], rmx[ch[x][0]] + val[x]);
        lmx[x] = max(lmx[ch[x][0]], sum[ch[x][0]] + val[x]);
        lmx[x] = max(0, lmx[x]);
        rmx[x] = max(0, val[x] + rmx[ch[x][0]]);
    } else if (ch[x][1]) {
        sz[x] = sz[ch[x][1]] + 1;
        sum[x] = sum[ch[x][1]] + val[x];
        mx[x] = max(mx[ch[x][1]], lmx[ch[x][1]] + val[x]);
        rmx[x] = max(rmx[ch[x][1]], sum[ch[x][1]] + val[x]);
        rmx[x] = max(0, rmx[x]);
        lmx[x] = max(0, lmx[ch[x][1]] + val[x]);
    } else {
        sz[x] = 1, sum[x] = mx[x] = val[x];
        lmx[x] = rmx[x] = max(val[x], 0);
    }
}
inline void pushDown(int x) {
    int& ls = ch[x][0];
    int& rs = ch[x][1];
    if (lazy_rev[x]) {
        swap(ls, rs);
        if (ls) lazy_rev[ls] ^= 1, swap(lmx[ls], rmx[ls]);
        if (rs) lazy_rev[rs] ^= 1, swap(lmx[rs], rmx[rs]);
        lazy_rev[x] = 0;
    }
    if (lazy_mod[x]) {
        if (ls) lazy_mod[ls]=1,val[ls]=val[x],sum[ls]=val[x]*sz[ls],mx[ls]=max(sum[ls],val[ls]),lmx[ls]=rmx[ls]=max(sum[ls],0);
        if (rs) lazy_mod[rs]=1,val[rs]=val[x],sum[rs]=val[x]*sz[rs],mx[rs]=max(sum[rs],val[rs]),lmx[rs]=rmx[rs]=max(sum[rs],0);
        lazy_mod[x] = 0;
    }
}
void Split(int now, int k, int &x, int &y) {
    if (!now) {
        x = y = 0;
        return;
    } else { // <= to left, > to right
        pushDown(now);
        if (sz[ch[now][0]] + 1 <= k) x = now, Split(ch[now][1], k - sz[ch[now][0]] - 1, ch[now][1], y);
        else y = now, Split(ch[now][0], k, x, ch[now][0]);
        Update(now);
        // Split "by position"
    }
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
int build(int L = 1, int R = N) {
    if (L > R) return 0;
    int M = (L + R) / 2;
    int now = newNode(a[M]);
    ch[now][0] = build(L, M - 1);
    ch[now][1] = build(M + 1, R);
    Update(now);
    return now;
}
inline void Insert(int pos, int n) {
    int x, y;
    Split(root, pos, x, y);
//    printf("%d %d\n", x, y);
    int new_root = build(1, n);
    root = Merge(Merge(x, new_root), y);
}
inline void Del(int pos, int n) {
    int x, y, z;
    Split(root, pos + n - 1, x, z);
    Split(x, pos - 1, x, y);
    root = Merge(x, z);
    trash(y);
}
inline void Rev(int pos, int n) {
    int x, y, z;
    Split(root, pos + n - 1, x, z);
    Split(x, pos - 1, x, y);
    lazy_rev[y] ^= 1, swap(lmx[y], rmx[y]);
    root = Merge(Merge(x, y), z);
}
inline void Modify(int pos, int n, int c) {
    int x, y, z;
    Split(root, pos + n - 1, x, z);
    Split(x, pos - 1, x, y);
    lazy_mod[y]=1,val[y]=c,sum[y]=sz[y]*c,mx[y]=max(sum[y],val[y]),lmx[y]=rmx[y]=max(sum[y],0);
    root = Merge(Merge(x, y), z);
}
inline int getSum(int pos, int n){
    int x, y, z;
    Split(root, pos + n - 1, x, z);
    Split(x, pos - 1, x, y);
    int res = sum[y];
    root = Merge(Merge(x, y), z);
    return res;
}
int main() {
//    freopen("in.txt", "r", stdin);
    readin();
    root = build(1, N);
    char op[20]; int pos, n, c;
    while (M--) {
        scanf("%s", op);
        switch (op[0]) {
            case 'I':
                scanf("%d%d", &pos, &n);
                for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
                Insert(pos, n);
                break;
            case 'D':
                scanf("%d%d", &pos, &n);
                for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
                Del(pos, n);
                break;
            case 'R':
                scanf("%d%d", &pos, &n);
                Rev(pos, n);
                break;
            case 'G':
                scanf("%d%d", &pos, &n);
                printf("%d\n", getSum(pos, n));
                break;
            case 'M':
                if (op[2] == 'X'){
                    printf("%d\n", mx[root]);
                } else if (op[2] == 'K'){
                    scanf("%d%d%d", &pos, &n, &c);
                    Modify(pos, n, c);
                }
                break;
        }
    }
    return 0;
}
/*
15 36
-6 -5 -6 -5 -3 -3 -20 -100 -1 -50 -2 -30 -3 -20 -100 -1
GET-SUM 5 4
MAX-SUM
INSERT 8 3 -5 7 2
MAKE-SAME 5 3 -10
DELETE 12 1
DELETE 2 5
DELETE 10 8
MAX-SUM
MAKE-SAME 3 3 2
REVERSE 3 6
GET-SUM 5 4
INSERT 5 4 -10 -20 -30 -40
MAX-SUM
DELETE 10 1
MAX-SUM
DELETE 12 1
DELETE 2 5
MAKE-SAME 3 3 2
REVERSE 3 6
GET-SUM 5 4
INSERT 2 4 -4 -3 -2 -5
DELETE 10 1
MAX-SUM
REVERSE 2 10
GET-SUM 7 10
DELETE 2 5
MAKE-SAME 3 3 2
REVERSE 3 6
GET-SUM 5 4
INSERT 10 4 -107 -207 -370 -470
MAX-SUM
DELETE 10 1
MAX-SUM
DELETE 12 1
DELETE 2 5
MAX-SUM

*/

