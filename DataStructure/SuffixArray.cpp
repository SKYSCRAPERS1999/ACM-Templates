const int maxn = 1e5 + 11;
int N, M, T, P, Q;
int x[maxn], y[maxn], buc[maxn], Rank[maxn], Height[maxn];
int SA[maxn], s[maxn];
int cmp(int *s, int a, int b, int l) {
    return s[a] == s[b] && s[a + l] == s[b + l];
}
// m: the number of the biggest char + 1!!!
// n: length of the string to int
// Rank,SA:0-N-1, Height:1-N-1
void da(int *s, int n, int m) {
    for (int i = 0; i < m; i++) buc[i] = 0;
    for (int i = 0; i < n; i++) buc[x[i] = s[i]]++;
    for (int i = 1; i < m; i++) buc[i] += buc[i - 1];
    for (int i = n - 1; i >= 0; i--) SA[--buc[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1){
        int p = 0;
        for (int i = n - 1; i >= n - k; i--) y[p++] = i;
        for (int i = 0; i < n; i++) if (SA[i] >= k) y[p++] = SA[i] - k;
        for (int i = 0; i < m; i++) buc[i] = 0;
        for (int i = 0; i < n; i++) buc[x[y[i]]]++;
        for (int i = 1; i < m; i++) buc[i] += buc[i - 1];
        for (int i = n - 1; i >= 0; i--) SA[--buc[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1; x[SA[0]] = 0;
        for (int i = 1; i < n; i++) {
            x[SA[i]] = cmp(y, SA[i - 1], SA[i], k) ? p - 1 : p++;
        }
        if (p >= n) break;
        m = p;
    }
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
bool contain(string S, string T){
    int l = 0, r = S.length();
    while (l < r){
        int m = (l + r) / 2;
        if (S.compare(SA[m], T.length(), T) < 0) l = m + 1;
        else r = m;
    }
    return S.compare(SA[r], T.length(), T) == 0;
}
int main() {
    string A; cin >> A; N = A.length();
    for (int i = 0; i < N; i++) s[i] = A[i] - 'a' + 1;
    da(s, N, 26 + 1);
    build_height(s, N);
    return 0;
}
