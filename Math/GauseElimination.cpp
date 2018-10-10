const double eps = 1e-6;
const int maxn = 50 + 11;
int N, M, T, K;
double matrix[maxn][maxn + 1];
double ans[maxn];
void exchange(int p1,int p2,int n){
    double t; int i;
    for(i = 0; i <= n; i++) {t = matrix[p1][i], matrix[p1][i] = matrix[p2][i], matrix[p2][i] = t;}
}
bool gauss(int n){
    for (int i = 0, p; i < n - 1; i++){
        p = i;
        for (int j = i + 1; j < n; j++) if (fabs(matrix[j][i]) > fabs(matrix[p][i])) p = j;
        if (p != i) exchange(p, i, n);
        if (fabs(matrix[i][i]) < eps) return false;
        for (int j = n; j >= i; j--) matrix[i][j] /= matrix[i][i];
        for (int j = i + 1; j < n; j++){
            for (int k = n; k >= i; k--){
                matrix[j][k] -= matrix[i][k] * matrix[j][i];
            }
        }
    }
    for (int i = n - 1; i >= 0; i--){
        ans[i] = matrix[i][n];
        for (int j = i - 1; j >= 0; j--){
            matrix[j][n] -= matrix[i][n] * matrix[j][i];
        }
    }
    return true;
}
