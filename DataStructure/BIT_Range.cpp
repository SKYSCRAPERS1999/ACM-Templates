//d[i]: a[i]-a[i-1]
//bit1: d[i]
//bit2: i * d[i]
//a[n]: (n+1)*sum(d[i])-sum(i*d[i])
LL bit1[maxn], bit2[maxn]; int a[maxn], d[maxn];
void add(int i, int x, LL *bit){
    while (i <= N) bit[i] += 1LL * x, i += lowbit(i);
}
LL sum(int i, LL *bit){
    LL res = 0;
    while (i) res += 1LL * bit[i], i -= lowbit(i);
    return res;
}
int main(){
    cin >> N >> M;
    for (int i = 1; i <= N; i++) scanf("%d", &a[i]);
    adjacent_difference(a + 1, a + N + 1, d + 1);
    for (int i = 1; i <= N; i++) {
        add(i, d[i], bit1);
        add(i, 1LL*i*d[i], bit2);
    }
    int op, x, y, k;
    while (M--){
        scanf("%d", &op);
        if (op == 1){
            scanf("%d%d%d", &x, &y, &k);
            add(x, k, bit1); add(x, 1LL*x*k, bit2); // 修改x
            add(y + 1, -k, bit1); add(y + 1, -1LL*(y+1)*k, bit2); // 修改 y + 1
        }else{
            scanf("%d%d", &x, &y);
            LL sy = 1LL * (y + 1) * sum(y, bit1) - sum(y, bit2);
            LL sx = 1LL * x * sum(x - 1, bit1) - sum(x - 1, bit2);
            printf("%lld\n", sy - sx);
        }
    }
    return 0;
}
