#define F(o) ((o)/3+((o)%3==1?0:tb))
#define G(o) ((o)<tb?(o)*3+1:((o)-tb)*3+2)
int N, M, T, P, Q;
const int maxn = 1e5 + 11;
char S[maxn];
int buc[maxn], x[maxn], y[maxn], z[maxn], Rank[maxn], Height[maxn];
int s[3*maxn], SA[3*maxn];
int c0(int *s, int a, int b) {
    return s[a] == s[b] && s[a + 1] == s[b + 1] && s[a + 2] == s[b + 2];
}
int c12(int k, int *s, int a, int b) {
    if (k == 2) return s[a] < s[b] || s[a] == s[b] && c12(1, s, a + 1, b + 1);
    else return s[a] < s[b] || s[a] == s[b] && z[a + 1] < z[b + 1];
}
void Sort(int *s, int *a, int *b, int n, int m) {
    int i;
    for (i = 0; i < n; i++) z[i] = s[a[i]];
    for (i = 0; i < m; i++) buc[i] = 0;
    for (i = 0; i < n; i++) buc[z[i]]++;
    for (i = 1; i < m; i++) buc[i] += buc[i - 1];
    for (i = n - 1; i >= 0; i--) b[--buc[z[i]]] = a[i];
    return;
}
void dc3(int *s, int *SA, int n, int m) {
    int i, j, *rn = s + n, *san = SA + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
    s[n] = s[n + 1] = 0;
    for (i = 0; i < n; i++) if (i % 3 != 0) x[tbc++] = i;
    Sort(s + 2, x, y, tbc, m);
    Sort(s + 1, y, x, tbc, m);
    Sort(s, x, y, tbc, m);
    for (p = 1, rn[F(y[0])] = 0, i = 1; i < tbc; i++)
        rn[F(y[i])] = c0(s, y[i - 1], y[i]) ? p - 1 : p++;
    if (p < tbc) dc3(rn, san, tbc, p);
    else for (i = 0; i < tbc; i++) san[rn[i]] = i;
    for (i = 0; i < tbc; i++) if (san[i] < tb) y[ta++] = san[i] * 3;
    if (n % 3 == 1) y[ta++] = n - 1;
    Sort(s, y, x, ta, m);
    for (i = 0; i < tbc; i++) z[y[i] = G(san[i])] = i;
    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        SA[p] = c12(y[j] % 3, s, x[i], y[j]) ? x[i++] : y[j++];
    for (; i < ta; p++) SA[p] = x[i++];
    for (; j < tbc; p++) SA[p] = y[j++];
    return;
}
void build_height(int *s, int n) {
    int k = 0;
    for (int i = 0; i < n; i++) Rank[SA[i]] = i;
    for (int i = 0; i < n; i++) {
        if (Rank[i] == 0) {Height[0] = 0; continue;}
        if (k) k--;
        int j = SA[Rank[i] - 1];
        while (s[i + k] == s[j + k] && i + k < n && j + k < n) k++;
        Height[Rank[i]] = k;
    }
}
void init(int *s, int n){
    s[n] = 0;
    dc3(s, SA, n + 1, *max_element(s, s + n) + 1);
    for (int i = 0; i < n; i++) swap(SA[i], SA[i + 1]);
    build_height(s, n);
}
