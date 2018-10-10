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
inline int read() {
    int num = 0; char c; bool flag = false;
    while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
    if (c == '-') flag = true;
    else num = c - '0';
    while (isdigit(c = getchar())) num = num * 10 + c - '0';
    return (flag ? -1 : 1) * num;
}
int N, M, T, root, tot;
int sz[maxn], ch[maxn][2], rnd[maxn], val[maxn];
inline int newNode(int x) {
    sz[++tot] = 1; val[tot] = x;
    rnd[tot] = rand();
    return tot;
}
inline void Update(int x) {
    sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
}
void Split(int now, int k, int &x, int &y) {
    if (!now) {
        x = y = 0;
        return;
    } else { // <= to left, > to right
        if (val[now] <= k) x = now, Split(ch[now][1], k, ch[now][1], y);
        else y = now, Split(ch[now][0], k, x, ch[now][0]);
        Update(now);
        // The split is "by value", we can also change it to "by size".
    }
}
/*
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
*/
int Merge(int x, int y) {
    if (!x || !y) return x + y;
    if (rnd[x] < rnd[y]) {
        ch[x][1] = Merge(ch[x][1], y);
        Update(x);
        return x;
    } else {
        ch[y][0] = Merge(x, ch[y][0]);
        Update(y);
        return y;
    }
}
inline int Kth(int now, int k) {
    while (1) {
        if (k <= sz[ch[now][0]]) now = ch[now][0];
        else if (k == sz[ch[now][0]] + 1) return now;
        else k -= sz[ch[now][0]] + 1, now = ch[now][1];
    }
}
inline int Rank(int v) {
    int x, y;
    Split(root, v - 1, x, y);
    int res = sz[x] + 1;
    root = Merge(x, y);
    return res;
}
inline void Insert(int v) {
    int x, y;
    Split(root, v, x, y);
    root = Merge(Merge(x, newNode(v)), y);
}
inline void Del(int v) {
    int x, y, z;
    Split(root, v, x, z);
    Split(x, v - 1, x, y);
    y = Merge(ch[y][0], ch[y][1]);
    root = Merge(Merge(x, y), z);
}
inline int Pre(int v) {
    int x, y;
    Split(root, v - 1, x, y);
    int res = val[Kth(x, sz[x])];
    root = Merge(x, y);
    return res;
}
inline int Next(int v) {
    int x, y;
    Split(root, v, x, y);
    int res = val[Kth(y, 1)];
    root = Merge(x, y);
    return res;
}
int main() {
    srand(time(NULL));
    N = read();
    for (int i = 1, opt, x; i <= N; i++) {
        opt = read(); x = read();
        switch(opt) {
            case 1:
                Insert(x);
                break;
            case 2:
                Del(x);
                break;
            case 3:
                printf("%d\n", Rank(x));
                break;
            case 4:
                printf("%d\n", val[Kth(root, x)]);
                break;
            case 5:
                printf("%d\n", Pre(x));
                break;
            case 6:
                printf("%d\n", Next(x));
                break;
        }
    }
}
/*
10
1 106465
4 1
1 317721
1 460929
1 644985
1 84185
1 89851
6 81968
1 492737
5 493598

*/

