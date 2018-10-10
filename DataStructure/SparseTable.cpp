int mx[maxn][maxb], mi[maxn][maxb], a[maxn];
//Here is [1,N], [0,N) is also ok.
//We can also make 2 dimentions by mx[maxn][maxn][maxb] (square) or mx[maxn][maxb][maxn][maxb] (rectangle)
void pre() {
    for (int j = 0; j < maxb; j++) {
        for (int i = 1; i <= N; i++) {
            if (i + (1 << j) - 1 <= N) {
                mx[i][j] = (j ? max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]) : a[i]);
                mi[i][j] = (j ? min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]) : a[i]);
            }
        }
    }
}
int query(int l, int r) {
    int j = (int)(log2(r - l + 1));
    return max(mx[l][j], mx[r - (1 << j) + 1][j]) - min(mi[l][j], mi[r - (1 << j) + 1][j]);
}
