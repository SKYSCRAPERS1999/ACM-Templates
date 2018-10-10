#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 1e5 + 11;
int Next[maxn];
int slen, tlen;
string S, T;
void getNext() {
    int j, k;
    j = 0; k = -1; Next[0] = -1;
    while (j < tlen){
        if (k == -1 || T[j] == T[k]) Next[++j] = ++k;
        else k = Next[k];
    }
}
int KMP_Index() {
    int i = 0, j = 0;
    getNext();
    while (i < slen && j < tlen) {
        if (j == -1 || S[i] == T[j]) i++, j++;
        else j = Next[j];
    }
    if (j == tlen) return i - tlen;
    else return -1;
}
int KMP_Count() {
    int ans = 0;
    int i, j = 0;
    if (slen == 1 && tlen == 1) {
        if (S[0] == T[0]) return 1;
        else return 0;
    }
    getNext();
    for (i = 0; i < slen; i++) {
        while (j > 0 && S[i] != T[j]) j = Next[j];
        if (S[i] == T[j]) j++;
        if (j == tlen) ans++, j = Next[j];
    }
    return ans;
}
int main() {

    int TT;
    int i, cc;
    cin >> TT;
    while (TT--) {
        cin >> S >> T;
        slen = S.size();
        tlen = T.size();
        cout << KMP_Index() << endl;
        cout << KMP_Count() << endl;
    }
    return 0;
}
/*
4
aaaaaa a
abcd d
aabaa b
*/
