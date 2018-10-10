const int maxn = 2e3 + 11;
int N, M, T;

int match[maxn];
int lx[maxn],ly[maxn];
int sx[maxn],sy[maxn];
int weight[maxn][maxn];
int dfs(int x) {
    sx[x]=true;
    for(int i=0; i<M; i++) {
        if(!sy[i]&&lx[x]+ly[i]==weight[x][i]) {
            sy[i]=true;
            if(match[i]==-1||dfs(match[i])) {
                match[i]=x;
                return true;
            }
        }
    }
    return false;
}
int fax(int x) { // x: 0->minimum, 1->maximum
    if(!x) {
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                weight[i][j]=-weight[i][j];
            }
        }
    }
    memset(match,-1,sizeof(match));
    for(int i=0; i<N; i++) {
        ly[i]=0;
        lx[i]=-INF;
        for(int j=0; j<M; j++) {
            if(weight[i][j]>lx[i]) {
                lx[i]=weight[i][j];
            }
        }
    }
    for(int i=0; i<N; i++) {
        while(1) {
            memset(sx,0,sizeof(sx));
            memset(sy,0,sizeof(sy));
            if(dfs(i))
                break;
            int mic=INF;
            for(int j=0; j<N; j++) {
                if(sx[j]) {
                    for(int k=0; k<M; k++) {
                        if(!sy[k]&&lx[j]+ly[k]-weight[j][k]<mic) {
                            mic=lx[j]+ly[k]-weight[j][k];
                        }
                    }
                }
            }
            if(mic==0)
                return -1;
            for(int j=0; j<N; j++)
                if(sx[j]) {
                    lx[j]-=mic;
                }
            for(int j=0; j<M; j++)
                if(sy[j]) {
                    ly[j]+=mic;
                }
        }
    }
    int sum=0;
    for(int i=0; i<M; i++) {
        if(match[i]>=0) {
            sum+=weight[match[i]][i];
        }
    }
    if(!x) {
        sum=-sum;
    }
    return sum;
}
