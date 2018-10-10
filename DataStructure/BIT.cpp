//可用“差分”想法实现单点查询，区间更新
//具体的:
//初始化:add(i, a[i]-a[i-1]) for all i
//查询: sum(i)
//更新: add(i, k), add(j + 1, -k)

int bit[maxn];
void add(int i, int x){
    while (i <= N) bit[i] += x, i += lowbit(i);
}
int sum(int i){
    int res = 0;
    while (i > 0) res += bit[i], i -= lowbit(i);
    return res;
}


