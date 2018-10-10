const int MOD = 1e9 + 7;
int N, M, T, K;
LL mat[maxn][maxn];
//By gauss elimination and the idea of gcd
LL det(int n) {
    LL ans = 1, f = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = i, y = j;
            while (mat[y][i]) {
                LL t = mat[x][i] / mat[y][i];
                for (int k = i; k < n; k++)
                    mat[x][k] = (mat[x][k] - mat[y][k] * t % MOD) % MOD;
                swap(x, y);
                print();
            }
            if (x != i) {
                for (int k = 0; k < n; k++)
                    swap(mat[i][k], mat[j][k]);
                f = -f;
            }
        }
        ans = ans * mat[i][i] % MOD;
    }
    return (ans * f + MOD) % MOD;
}
