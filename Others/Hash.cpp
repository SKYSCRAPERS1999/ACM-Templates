#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
//For a given string, construct all cyclic shifts, sort them lexicographically,
//output the last column, and find the position of the original string in this list.
using namespace std;
typedef unsigned long long ULL;
const int INF = 0x3f3f3f3f;
const int maxn = 1e5 + 11;
int N, M, T;
char data[maxn]; string S;
void readin(){
    scanf("%s", data);
    S = string(data);
    N = S.size();
    S += S;
}
struct PolyHash {
    // -------- Static variables --------
    static const int mod = (int)1e9 + 123; // prime mod of polynomial hashing
    static vector<int> pow1;        // powers of base modulo mod
    static vector<ULL> pow2;        // powers of base modulo 2^64
    static int base;                     // base (point of hashing)
    // --------- Static functons --------
    static inline int diff(int a, int b) {
        return (a -= b) < 0 ? a + mod : a;
    }
    // -------------- Variables of class -------------
    vector<int> pref1; // Hash on prefix modulo mod
    vector<ULL> pref2; // Hash on prefix modulo 2^64
    // Cunstructor from string:
    PolyHash(const string& s):pref1(s.size()+1u,0),pref2(s.size()+1u,0){
        assert(base < mod);
        const int n = s.size(); // Firstly calculated needed power of base:
        while ((int)pow1.size() <= n) {
            pow1.push_back(1LL * pow1.back() * base % mod);
            pow2.push_back(pow2.back() * base);
        }
        for (int i = 0; i < n; ++i) { // Fill arrays with polynomial hashes on prefix
            assert(base > s[i]);
            pref1[i+1] = (pref1[i] + 1LL * s[i] * pow1[i]) % mod;
            pref2[i+1] = pref2[i] + s[i] * pow2[i];
        }
    }
    // Polynomial hash of subsequence [pos, pos+len)
    // If mxPow != 0, value automatically multiply on base in needed power. Finally base ^ mxPow
    inline pair<int, ULL> operator()(const int pos, const int len, const int mxPow = 0) const {
        int hash1 = pref1[pos+len] - pref1[pos];
        ULL hash2 = pref2[pos+len] - pref2[pos];
        if (hash1 < 0) hash1 += mod;
        if (mxPow != 0) {
            hash1 = 1LL * hash1 * pow1[mxPow-(pos+len-1)] % mod;
            hash2 *= pow2[mxPow-(pos+len-1)];
        }
        return make_pair(hash1, hash2);
    }
};
int PolyHash::base(233);
vector<int> PolyHash::pow1{1};
vector<ULL> PolyHash::pow2{1};

void solve(){
    static int mxPow = 2*N;
    static PolyHash hs(S);
    vector<int> id(N);
    iota(id.begin(), id.end(), 0);
    stable_sort(id.begin(), id.end(), [&](const int &i, const int &j) {
            int left = 0, right = N + 1;
            while (left < right) {
                int mid = (left + right + 1) / 2;
                if (hs(i, mid, mxPow) == hs(j, mid, mxPow)) left = mid;
                else right = mid - 1;
            }
            return left <= N && S[i + left] < S[j + left];
         }
    );
    string ans; int pos = -1;
    for (int i = 0; i < id.size(); i++) {
        int j = id[i];
        if (j == 0 && pos == -1) pos = i;
        ans.push_back(S[j + N - 1]);
    }
    printf("%d\n%s\n", pos + 1, ans.c_str());
}
int main(){
    readin();
    solve();
    return 0;
}

