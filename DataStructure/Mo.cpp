const int maxn = 5e4 + 11;
int N, M, S, n, col[maxn];
int blk[maxn]; LL cnt[maxn], ans1[maxn], ans2[maxn];
struct D{
    int l, r, id;
    bool operator < (const D& rhs) const{
        return blk[l] < blk[rhs.l] || (blk[l] == blk[rhs.l] && r < rhs.r);
    }
} q[maxn];
inline void upd(LL &sum, int c, int x){
    sum -= cnt[c] * cnt[c];
    cnt[c] += x;
    sum += cnt[c] * cnt[c];
}
int main(){
    cin >> N >> M; S = int(sqrt(N)) + 1;
    for (int i = 1; i <= N; i++) scanf("%d", &col[i]);
    for (int i = 1; i <= N; i++) blk[i] = (i - 1) / S;
    for (int i = 0, l, r; i < M; i++){
        scanf("%d%d", &l, &r);
        q[i] = {l, r, i};
    }
    sort(q, q + M);
    int L = 1, R = 0; LL sum = 0;
    for (int i = 0; i < M; i++){
        while (L < q[i].l) upd(sum, col[L++], -1);
        while (R > q[i].r) upd(sum, col[R--], -1);
        while (L > q[i].l) upd(sum, col[--L], 1);
        while (R < q[i].r) upd(sum, col[++R], 1);
        if (q[i].l == q[i].r) {
            ans1[q[i].id] = 0, ans2[q[i].id] = 1;
            continue;
        }
        ans1[q[i].id] = sum - (R - L + 1);
        ans2[q[i].id] = 1LL * (R - L + 1) * (R - L);
    }
    for (int i = 0; i < M; i++) {
        LL j = __gcd(ans1[i], ans2[i]);
        printf("%lld/%lld\n", ans1[i] / j, ans2[i] / j);
    }
    return 0;
}
