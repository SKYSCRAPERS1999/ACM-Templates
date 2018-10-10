list<int> lis(){
    vector<int> M(a.size() + 1, INF);
    int *p = new int[a.size() + 1];
    memset(p, -1, sizeof(p));
    int len = 0;
    for (int i = 0; i < a.size(); i++){
        int pos = lower_bound(M.begin(), M.end(), a[i]) - M.begin();
        p[a[i]] = pos ? M[pos - 1] : -1;
        M[pos] = a[i];
        if (pos + 1 > len) len = pos + 1;
    }
    list<int> res;
    for (int x = M[len - 1]; x >= 0; x = p[x]) res.push_front(x);
    return res;
}
