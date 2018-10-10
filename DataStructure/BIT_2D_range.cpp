#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&(-(x)))
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int maxn = 2048 + 11;
int read() {
    int num = 0; char c; bool flag = false;
    while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
    if (c == '-') flag = true;
    else num = c - '0';
    while (isdigit(c = getchar())) num = num * 10 + c - '0';
    return (flag ? -1 : 1) * num;
}
int N, M, T; char op[5];
int bit1[maxn][maxn], bit2[maxn][maxn], bit3[maxn][maxn], bit4[maxn][maxn];
void add(int n, int m, int x){
    for (int i = n; i <= N; i += lowbit(i)) {
        for (int j = m; j <= M; j += lowbit(j)) {
            bit1[i][j] += x;
            bit2[i][j] += n*x;
            bit3[i][j] += m*x;
            bit4[i][j] += n*m*x;
        }
    }
}
int sum(int n, int m){
    int res = 0;
    for (int i = n; i > 0; i -= lowbit(i)) {
        for (int j = m; j > 0; j -= lowbit(j)) {
            res += (n+1)*(m+1)*bit1[i][j];
            res -= (m+1)*bit2[i][j];
            res -= (n+1)*bit3[i][j];
            res += bit4[i][j];
        }
    }
    return res;
}

int main(){
    scanf("%s%d%d", op, &N, &M);
    while (scanf("%s", op) != EOF){
        int a = read(), b = read(), c = read(), d = read();
        if (op[0] == 'L') {
            int x = read();
            add(a, b, x);
            add(a, d + 1, -x);
            add(c + 1, b, -x);
            add(c + 1, d + 1, x);
        } else {
            int ans = sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
            printf("%d\n", ans);
        }
    }
    return 0;
}
/*
  \sum_{i=1}^x\sum_{j=1}^y (d[i][j]*(x-i+1)*(y-j+1))
= \sum_{i=1}^x\sum_{j=1}^y (d[i][j]*(x+1)*(y+1)−d[i][j]*i*(y+1)−d[i][j]*j*(x+1)+d[i][j]*i*j)
维护:
d[i][j],d[i][j]*i,d[i][j]*j,d[i][j]*i*j
*/

