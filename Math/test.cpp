#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<bitset>
#include<cstdlib>
#include<cmath>
#include<set>
#include<list>
#include<deque>
#include<map>
#include<queue>
#include<sstream>
#include<complex>
#define lowbit(x) ((-x)&(x))
using namespace std;
typedef long long LL;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int MAXN = 2000 + 11;
int N, M, T, cc;
struct Edge
{
    int v;
    int w;
    int next;
} edge[MAXN];
int head[25], d[25], vis[25], cnt[25];
int r[25], t[25], s[25];
void addedge(int u, int v, int w)
{
    edge[cc].v = v;
    edge[cc].w = w;
    edge[cc].next = head[u];
    head[u] = cc++;
}
bool spfa(int vv)
{
    int x, i, e;
    for (i = 0; i <= 24; i++)
    {
        d[i] = -INF;
        cnt[i] = 0;
    }
    d[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        x = q.front();
        q.pop();
        vis[x] = 0;
        for (int e = head[x]; e != -1; e = edge[e].next)
        {
            if (d[edge[e].v] < d[x] + edge[e].w)
            {
                d[edge[e].v] = d[x] + edge[e].w;
                if (!vis[edge[e].v])
                {
                    q.push(edge[e].v);
                    vis[edge[e].v] = 1;

                    cnt[edge[e].v]++;
                    if (cnt[edge[e].v] > 24)
                    {
                        return false;
                    }
                }
            }
        }
    }
    if (d[24] == vv) return true;
    else return false;
}
void build(int x)
{
    cc = 0;
    memset(edge, 0, sizeof(edge));
    memset(head, -1, sizeof(head));
    memset(d, 0, sizeof(d));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    int i, j;
    for (i = 1; i <= 24; i++)
    {
        addedge(i - 1, i, 0);
        addedge(i, i - 1, -t[i]);
    }
    addedge(0, 24, x);
    for (i = 1; i <= 24; i++)
    {
        if (i >= 1 && i < 8)
        {
            addedge(i + 16, i, r[i] - x);
        }
        else
        {
            addedge(i - 8, i, r[i]);
        }
    }
}
void solve()
{
    int i;
    for (i = 0; i <= N; i++)
    {
        build(i);
        if (spfa(i))
        {
            printf("%d\n", i);
            return;
        }
    }
    printf("No Solution\n");
    return;
}
int main()
{
    cin >> T;
    freopen("output","w",stdout);
    while (T--)
    {
        int i, tmp;
        for (i = 1; i <= 24; i++)
        {
            scanf("%d", &r[i]);
        }
        scanf("%d", &N);
        for (i = 1; i <= N; i++)
        {
            scanf("%d", &tmp);
            t[tmp + 1]++;
        }
        solve();
    }
    return 0;
}
