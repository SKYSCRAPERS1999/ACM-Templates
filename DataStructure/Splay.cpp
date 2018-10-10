#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000
int ch[MAXN][2], f[MAXN], sz[MAXN], cnt[MAXN], key[MAXN];
int n, root;
inline void _clear(int x) {
    ch[x][0] = ch[x][1] = f[x] = sz[x] = cnt[x] = key[x] = 0;
}
inline bool _get(int x) {
    return ch[f[x]][1] == x;
}
inline void _update(int x) {
    if (x) {
        sz[x] = cnt[x];
        if (ch[x][0]) sz[x] += sz[ch[x][0]];
        if (ch[x][1]) sz[x] += sz[ch[x][1]];
    }
}
inline void _rotate(int x) {
    int old = f[x], oldf = f[old], whichx = _get(x);
    ch[old][whichx] = ch[x][whichx ^ 1]; f[ch[old][whichx]] = old;
    ch[x][whichx ^ 1] = old; f[old] = x;
    f[x] = oldf;
    if (oldf)
        ch[oldf][ch[oldf][1] == old] = x;
    _update(old); _update(x);
}
inline void splay(int x) {
    for (int fa; fa = f[x]; _rotate(x))
        if (f[fa])
            _rotate((_get(x) == _get(fa)) ? fa : x);
    root = x;
}
inline void _insert(int x) {
    if (root == 0) {
        n++;
        ch[n][0] = ch[n][1] = f[n] = 0;
        root = n;
        sz[n] = cnt[n] = 1;
        key[n] = x;
        return;
    }
    int now = root, fa = 0;
    while(1) {
        if (x == key[now]) {
            cnt[now]++; _update(now); _update(fa); splay(now); break;
        }
        fa = now;
        now = ch[now][key[now] < x];
        if (now == 0) {
            n++;
            ch[n][0] = ch[n][1] = 0;
            f[n] = fa;
            sz[n] = cnt[n] = 1;
            ch[fa][key[fa] < x] = n;
            key[n] = x;
            _update(fa);
            splay(n);
            break;
        }
    }
}
inline int _find(int x) {
    int now = root, ans = 0;
    while(1) {
        if (x < key[now])
            now = ch[now][0];
        else {
            ans += (ch[now][0] ? sz[ch[now][0]] : 0);
            if (x == key[now]) {
                splay(now); return ans + 1;
            }
            ans += cnt[now];
            now = ch[now][1];
        }
    }
}
inline int _findx(int x) {
    int now = root;
    while(1) {
        if (ch[now][0] && x <= sz[ch[now][0]])
            now = ch[now][0];
        else {
            int temp = (ch[now][0] ? sz[ch[now][0]] : 0) + cnt[now];
            if (x <= temp) return key[now];
            x -= temp; now = ch[now][1];
        }
    }
}
inline int _pre() {
    int now = ch[root][0];
    while (ch[now][1]) now = ch[now][1];
    return now;
}
inline int _next() {
    int now = ch[root][1];
    while (ch[now][0]) now = ch[now][0];
    return now;
}
inline void _del(int x) {
    int whatever = _find(x);
    if (cnt[root] > 1) {
        cnt[root]--;
        _update(root);
        return;
    }
    if (!ch[root][0] && !ch[root][1]) {
        _clear(root);
        root = 0;
        return;
    }
    if (!ch[root][0]) {
        int oldroot = root; root = ch[root][1]; f[root] = 0; _clear(oldroot); return;
    }
    else if (!ch[root][1]) {
        int oldroot = root; root = ch[root][0]; f[root] = 0; _clear(oldroot); return;
    }
    int leftbig = _pre(), oldroot = root;
    splay(leftbig);
    ch[root][1] = ch[oldroot][1];
    f[ch[oldroot][1]] = root;
    _clear(oldroot);
    _update(root);
}
int main() {
    int n, opt, x;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &opt, &x);
        switch(opt) {
        case 1: _insert(x); break;
        case 2: _del(x); break;
        case 3: printf("%d\n", _find(x)); break;
        case 4: printf("%d\n", _findx(x)); break;
        case 5: _insert(x); printf("%d\n", key[_pre()]); _del(x); break;
        case 6: _insert(x); printf("%d\n", key[_next()]); _del(x); break;
        }
    }
}

