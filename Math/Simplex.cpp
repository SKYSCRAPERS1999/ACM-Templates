/*
这是一道模板题。
本题中你需要求解一个标准型线性规划：
有 nn 个实数变量 x1,x2,…,xnx1,x2,…,xn 和 mm 条约束，其中第 ii 条约束形如 ∑nj=1aijxj≤bi∑j=1naijxj≤bi。
此外这 nn 个变量需要满足非负性限制，即 xj≥0xj≥0。
在满足上述所有条件的情况下，你需要指定每个变量 xjxj 的取值，使得目标函数 F=∑nj=1cjxjF=∑j=1ncjxj 的值最大。
输入格式
第一行三个正整数 n,m,t n,m,t。其中 t∈{0,1}t∈{0,1}。
第二行有 nn 个整数 c1,c2,⋯,cnc1,c2,⋯,cn，整数间均用一个空格分隔。
接下来 mm 行，每行代表一条约束，其中第 ii 行有 n+1n+1 个整数 ai1,ai2,⋯,ain,biai1,ai2,⋯,ain,bi，整数间均用一个空格分隔。
输出格式
如果不存在满足所有约束的解，仅输出一行 "Infeasible"。
如果对于任意的 MM，都存在一组解使得目标函数的值大于 MM，仅输出一行"Unbounded"。
否则，第一行输出一个实数，表示目标函数的最大值 FF。当第一行与标准答案的相对误差或绝对误差不超过 10−610−6，你的答案被判为正确。
如果 t=1t=1，那么你还需要输出第二行，用空格隔开的 nn 个非负实数，表示此时 x1,x2,…,xnx1,x2,…,xn 的取值，如有多组方案请任意输出其中一个。
判断第二行是否合法时，我们首先检验 F−∑nj=1cjxjF−∑j=1ncjxj 是否为 00，再对于所有 ii，检验 min{0,bi−∑nj=1aijxj}min{0,bi−∑j=1naijxj} 是否为 00。检验时我们会将其中大于 00 的项和不大于 00 的项的绝对值分别相加得到 S+S+ 和 S−S−，如果 S+S+ 和 S−S− 的相对误差或绝对误差不超过 10−610−6，则判为正确。
如果 t=0t=0，或者出现 Infeasible 或 Unbounded 时，不需要输出第二行。
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 200;
const double eps = 1e-6;
const int maxn = 1000;
double a[N][N], ans[N];
int n, m, t, id[N << 1];
int MM, NN, TT;
void pivot(int l, int e) {
    swap(id[e], id[n + l]);
    double r = a[l][e]; a[l][e] = 1;
    for (int j = 0; j <= n; ++j)
        a[l][j] /= r;
    for (int i = 0; i <= m; ++i)
        if (i != l) {
            r = a[i][e]; a[i][e] = 0;
            for (int j = 0; j <= n; ++j)
                a[i][j] -= r * a[l][j];
        }
}
void read(){
    scanf("%d%d%d", &n, &m, &t);
    for (int j = 1; j <= n; ++j) scanf("%lf", &a[0][j]), id[j] = j;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j)
            scanf("%lf", &a[i][j]);
        scanf("%lf", &a[i][0]);
    }
}
bool solve(){
    int i, j, l, e; double k, kk;
    while (true) {
        l = e = 0; k = -eps;
        for (i = 1; i <= m; ++i)
            if (a[i][0] < k) {
                k = a[i][0];
                l = i;
            }
        if (!l) break;
        k = -eps;
        for (j = 1; j <= n; ++j)
            if (a[l][j] < k && (!e || (rand() & 1))) {
                k = a[l][j];
                e = j;
            }
        if (!e) {puts("Infeasible"); return false;}
        pivot(l, e);
    }
    while (true) {
        for (j = 1; j <= n; ++j)
            if (a[0][j] > eps)
                break;
        if ((e = j) > n) break;
        k = 1e18; l = 0;
        for (i = 1; i <= m; ++i)
            if (a[i][e] > eps && (kk = (a[i][0] / a[i][e])) < k) {
                k = kk;
                l = i;
            }
        if (!l) {puts("Unbounded"); return false;}
        pivot(l, e);
    }
    return true;
}
int main() {
    scanf("%d", &TT);
    while (TT--){
        // 每次必须清空！！！
        memset(a, 0, sizeof(a)); memset(ans, 0, sizeof(ans)); memset(id, 0, sizeof(id));
        read();
        bool ok = solve(); if (!ok) continue;
        printf("%.10lf\n", -a[0][0]);
        if (!t) return 0;
        for (int i = 1; i <= m; ++i) ans[id[n + i]] = a[i][0];
        for (int i = 1; i <= n; ++i) printf("%.10lf ", ans[i]);
        eend: ;
    }
    return 0;
}
