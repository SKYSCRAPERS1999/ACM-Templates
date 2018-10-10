const int maxn = 1e4 + 11;
const int maxb = 63;
int N, T, Q;
LL a[maxn], b[100];
vector<LL> base;
void pre(){
    base.clear(); memset(b, 0, sizeof(b));
    for (int i = 0; i < N; i++){
        for (int j = maxb; j >= 0; j--){
            if ((a[i] >> j) & 1LL){
                if (b[j]) a[i] ^= b[j];
                else{
                    b[j] = a[i];
                    for (int k = j - 1; k >= 0; k--) if (b[k] && ((b[j] >> k) & 1LL)) b[j] ^= b[k];
                    for (int k = j + 1; k <= maxb; k++) if ((b[k] >> j) & 1LL) b[k] ^= b[j];
                    break;
                }
            }
        }
    }
    for (int i = 0; i <= maxb; i++) if (b[i]) base.push_back(b[i]);
}
