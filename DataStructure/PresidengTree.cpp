const int maxn = 1e5 + 11;
int Rank[maxn], root[maxn], cnt;
int N, Q;
struct Node{
    int sum, lson, rson;
    Node(){sum = lson = rson = 0;}
}T[maxn<<5];
int CreateNode(int sum, int lson, int rson){
    int idx = ++cnt;
    T[idx].sum = sum;
    T[idx].lson = lson;
    T[idx].rson = rson;
    return idx;
}
void Insert(int& root, int prt, int pos, int L, int R){
    root = CreateNode(T[prt].sum + 1, T[prt].lson, T[prt].rson);
    if (L == R) return;
    int M = (L + R) / 2;
    if (pos <= M) Insert(T[root].lson, T[prt].lson, pos, L, M);
    if (pos > M) Insert(T[root].rson, T[prt].rson, pos, M + 1, R);
}
int Query(int i, int j, int L, int R, int k){
    if (L == R) return L;
    int M = (L + R) / 2;
    int sum = T[T[j].lson].sum - T[T[i].lson].sum;
    if (k <= sum) return Query(T[i].lson, T[j].lson, L, M, k);
    else return Query(T[i].rson, T[j].rson, M + 1, R, k - sum);
}
int main() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) scanf("%d", &a[i].first), a[i].second = i;
    sort(a + 1, a + N + 1);
    for (int i = 1; i <= N; i++) Rank[a[i].second] = i;
    cnt = root[0] = 0;
    for (int i = 1; i <= N; i++){
        Insert(root[i], root[i - 1], Rank[i], 1, N);
    }
    while (Q--){
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int pos = Query(root[l - 1], root[r], 1, N, k);
        printf("%d\n", a[pos].first);
    }
    return 0;
}
