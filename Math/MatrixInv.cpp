#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1000 + 11;
const int MOD = 1e9 + 7;
LL Mat[maxn][maxn], Inv[maxn][maxn];
LL qpow(LL x, LL n) {
    LL res = 1;
    x = (x % MOD + MOD) % MOD;
    while (n > 0LL) {
        if (n & 1LL) res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return res;
}
void getInv(int n) {
    int p; LL t;
    for (int i = 0; i < n; i++) Inv[i][i] = 1;
    for (int i = 0; i < n; i++) {
        p = i;
        for (int j = i + 1; j < n; j++)
            if (abs(Mat[j][i]) > abs(Mat[p][i])) p = j;
        for (int j = 0; j < n; j++) {
            swap(Mat[i][j], Mat[p][j]);
            swap(Inv[i][j], Inv[p][j]);
        }
        t = qpow(Mat[i][i], MOD - 2);
        for (int j = 0; j < n; j++) {
            Mat[i][j] = (Mat[i][j] * t) % MOD;
            Inv[i][j] = (Inv[i][j] * t) % MOD;
        }
        for (int j = 0; j < n; j++){
            if (i != j && Mat[j][i] != 0) {
                t = Mat[j][i];
                for (int k = 0; k < n; k++) {
                    Mat[j][k] = (Mat[j][k] - (Mat[i][k] * t) % MOD) % MOD;
                    Inv[j][k] = (Inv[j][k] - (Inv[i][k] * t) % MOD) % MOD;
                }
            }
        }
    }
}
int main(){
    Mat[0][0]=93;Mat[0][1]=2;Mat[0][2]=3;
    Mat[1][0]=5;Mat[1][1]=7;Mat[1][2]=10;
    Mat[2][0]=2;Mat[2][1]=99;Mat[2][2]=5;
    getInv(3);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            LL t=0;
            for(int k=0;k<3;k++) t=(((t+Mat[i][k]*Inv[k][j])%MOD)+MOD)%MOD;
            cout<<t<<" \n"[j==2];
        }
    }
}
