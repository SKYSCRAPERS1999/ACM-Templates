#include<bits/stdc++.h>
using namespace std; typedef long long LL;
const int maxn = 1e6 + 11;
const int MOD = 1e9 + 7;
int N, M, T;
vector<int> prime;
bool checked[maxn];
int phi[maxn], mu[maxn];
int smu[maxn], sphi[maxn];
int d[maxn], e[maxn], md[maxn];
LL inv[maxn];
//Linear Seives
void get_prime(int n){
    memset(checked, 0, sizeof(checked)); prime.clear();
    for (int i = 2; i <= n; i++){
        if (!checked[i]) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= n; j++){
            checked[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}
void get_phi(int n){
    memset(checked, 0, sizeof(checked)); prime.clear();
    phi[1] = 1;
    for (int i = 2; i <= n; i++){
        if (!checked[i]) {prime.push_back(i); phi[i] = i - 1;}
        for (int j = 0; j < prime.size() && i * prime[j] <= n; j++){
            checked[i * prime[j]] = true;
            if (i % prime[j] == 0) {phi[i * prime[j]] = phi[i] * prime[j]; break;}
            else {phi[i * prime[j]] = phi[i] * (prime[j] - 1);}
        }
    }
}
void get_mu(int n){
    memset(checked, 0, sizeof(checked)); prime.clear();
    mu[1] = 1;
    for (int i = 2; i <= n; i++){
        if (!checked[i]) {prime.push_back(i); mu[i] = -1;}
        for (int j = 0; j < prime.size() && i * prime[j] <= n; j++){
            checked[i * prime[j]] = true;
            if (i % prime[j] == 0) {mu[i * prime[j]] = 0; break;}
            else {mu[i * prime[j]] = -mu[i];}
        }
    }
}
//Linear getting inverse mod MOD
void get_inv(LL n){
    inv[1] = 1;
    for (LL i = 2; i <= n; i++){
        inv[i] = 1LL * (MOD - (MOD / i)) * inv[MOD % i] % MOD;
    }
}
void get_facnum(int n){
    //md is the minimum divisor
    md[1] = d[1] = 1;
    for(int i = 2; i <= n; i++){
        if(!checked[i]){
            prime.push_back(i);
            d[i] = 2; e[i] = 1;
            md[i] = i;
        }
        for (int j = 0; j < prime.size() && i * prime[j] <= n; j++){
            int &curp = prime[j];
            checked[i * curp] = true;
            md[i * curp] = curp;
            if(i % curp == 0){
                d[i * curp] = d[i] / (e[i] + 1) * (e[i] + 2);
                e[i * curp] = e[i] + 1;
                break;
            }
            d[i * curp] = d[i] * 2;
            e[i * curp] = 1;
        }
    }
}

int main(){
    get_phi(1e4); get_mu(1e4);
    int UB = 100; int sum = 0; smu[0] = 0;
    for (int i = 1; i <= UB; i++) smu[i] = smu[i - 1] + mu[i];
    // Accelerating summation skill
    for (int i = 1, last; i <= UB; i = last + 1){
        last = UB / (UB / i);
        sum += (UB / i) * (UB / i + 1) / 2 * (smu[last] - smu[i - 1]);
    }
    cout << sum << endl;
    return 0;
}

