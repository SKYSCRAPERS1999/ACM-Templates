int N, M, K;
int a[maxn], X[maxn], x[maxn];
int qX[maxn], qx[maxn], s1, s2, t1, t2;
int main() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) scanf("%d", &a[i]);
    for (int i = 0; i < N; i++) {
        while (s1 < t1 && a[qX[t1 - 1]] < a[i]) t1--;
        qX[t1++] = i;
        if (i - K + 1 >= 0) X[i - K + 1] = a[qX[s1]];
        if (i - K + 1 == qX[s1]) s1++;

        while (s2 < t2 && a[qx[t2 - 1]] > a[i]) t2--;
        qx[t2++] = i;
        if (i - K + 1 >= 0) x[i - K + 1] = a[qx[s2]];
        if (i - K + 1 == qx[s2]) s2++;
    }
    for (int i = 0; i + K - 1 < N; i++) printf("%d%c", x[i], " \n"[i + K - 1 == N - 1]);
    for (int i = 0; i + K - 1 < N; i++) printf("%d%c", X[i], " \n"[i + K - 1 == N - 1]);
    return 0;
}

/*
1
10 6 10 5 5 5 5
3 2 2 1 5 7 6 8 2 9

*/
