#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&(-(x)))
#define MP make_pair
#define fi first
#define se second
// to replace or to modify!
#define LC(o) ((o)*2)
#define RC(o) ((o)*2+1)
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int maxn = 1e5 + 11;
int N, M, T;
struct E{
    double h; int l, r, f;
    bool operator < (const E& rhs) const {
        return h < rhs.h || (h == rhs.h && f > rhs.f);
    }
};
vector<E> lines;
double xl[maxn], yl[maxn], xr[maxn], yr[maxn];
vector<double> sorted;
double rev[maxn];

int mx[maxn<<3], mi[maxn<<3]; int cnt[maxn<<3];
void build(int L = 1, int R = M, int o = 1) {
    cnt[o] = mi[o] = mx[o] = 0;
    if (L == R) return;
    int M = (L + R) >> 1;
    build(L, M, LC(o));
    build(M + 1, R, RC(o));
}
void pushDown(int o) {
    if (cnt[o]) {
        cnt[LC(o)] += cnt[o]; cnt[RC(o)] += cnt[o];
        mi[LC(o)] += cnt[o]; mi[RC(o)] += cnt[o];
        mx[LC(o)] += cnt[o]; mx[RC(o)] += cnt[o];
        cnt[o] = 0;
    }
}
void update(int x1, int x2, int val, int L = 1, int R = M, int o = 1) {
    if (x1 <= L && R <= x2) {
        cnt[o] += val;
        mi[o] += val;
        mx[o] += val;
        return;
    }
    pushDown(o);
    int M = (L + R) >> 1;
    if (x1 <= M) update(x1, x2, val, L, M, LC(o));
    if (x2 > M) update(x1, x2, val, M + 1, R, RC(o));
    mi[o] = min(mi[LC(o)], mi[RC(o)]);
    mx[o] = max(mx[LC(o)], mx[RC(o)]);
}
//这里求的是至少覆盖两次的面积
double query(int L = 1, int R = M, int o = 1) { 
    if (mi[o] >= 2) return rev[R+1] - rev[L];
    pushDown(o);
    double ans = 0.0;
    int M = (L + R) / 2;
    if (mx[LC(o)] >= 2) ans += query(L, M, LC(o));
    if (mx[RC(o)] >= 2) ans += query(M + 1, R, RC(o));
    return ans;
}

int main(){
    cin >> T;
    while (T--){
        cin >> N;
        double ans = 0;
        lines.clear(); sorted.clear();

        for (int i = 0; i < N; i++) {
            scanf("%lf%lf%lf%lf", &xl[i], &yl[i], &xr[i], &yr[i]);
            sorted.push_back(xl[i]); sorted.push_back(xr[i]);
        }
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        for (int i = 0; i < N; i++) {
            int pos = lower_bound(sorted.begin(), sorted.end(), xl[i]) - sorted.begin() + 1;
            rev[pos] = xl[i];
            xl[i] = pos;
            pos = lower_bound(sorted.begin(), sorted.end(), xr[i]) - sorted.begin() + 1;
            rev[pos] = xr[i];
            xr[i] = pos;
        }

        M = sorted.size();
        for (int i = 0; i < N; i++){
            lines.push_back({yl[i],int(xl[i]),int(xr[i]),1});
            lines.push_back({yr[i],int(xl[i]),int(xr[i]),-1});
        }
        sort(lines.begin(), lines.end());

        build(1, M);
        update(lines[0].l, lines[0].r-1, lines[0].f, 1, M);
        for (int i = 1; i < 2*N; i++){
            ans += (lines[i].h-lines[i-1].h) * query();
            update(lines[i].l, lines[i].r-1, lines[i].f, 1, M);
        }

        printf("%.2f\n", ans);
    }
    return 0;
}
