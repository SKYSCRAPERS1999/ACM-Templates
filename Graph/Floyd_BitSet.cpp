const int maxn = 2016 + 1;
int N, M, T;
bitset<maxn> bit[maxn];
void floyd(){
    for (int k = 0; k < N; k++){
        for (int i = 0; i < N; i++){
            if (bit[i][k]) bit[i] = bit[i] | bit[k];
        }
    }
}
