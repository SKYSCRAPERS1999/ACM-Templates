#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

const double INF = 1e18 + 5;
const int maxn = 2e5 + 5;
const double eps = 1e-8;
int d_cmp(double x) {
    if(x<-eps) return -1;
    if(x>eps) return +1;
    return 0;
}
struct Point{
    double x,y;
    Point(double x=0, double y=0):x(x),y(y) {}
    bool operator<(const struct Point &rhs)const{
        if(d_cmp(x-rhs.x)==0)return d_cmp(y-rhs.y)<0;
        return d_cmp(x-rhs.x)<0;
    }
    bool operator==(const struct Point &rhs)const{
        return d_cmp(x-rhs.x)==0&&d_cmp(y-rhs.y)==0;
    }
}p[maxn], st[maxn];
double XMulti(Point a, Point b, Point c){ ///ac X ab
    return (c.x-a.x)*(b.y-a.y)-(b.x-a.x)*(c.y-a.y);
}
double dis(Point a, Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double dis2(Point a, Point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double DIS(Point a1, Point b, Point a2){
    return abs(XMulti(a1, b, a2))/dis(a1, a2);
}
double dot(Point a, Point b, Point c){ ///点积 ab . ac
    double s1=b.x-a.x;
    double t1=b.y-a.y;
    double s2=c.x-a.x;
    double t2=c.y-a.y;
    return s1*s2+t1*t2;
}

int ConvexHull(Point *p, int n, Point *st){ ///凸包
    sort(p,p+n);
    n=unique(p,p+n)-p; ///去重
    int m=0;
    for(int i=0; i<n; i++){
        while(m>1&&XMulti(st[m-2],p[i],st[m-1])<=0)
            m--;
        st[m++]=p[i];
    }
    int k=m;
    for(int i=n-2; i>=0; i--){
        while(m>k&&XMulti(st[m-2],p[i],st[m-1])<=0)
            m--;
        st[m++]=p[i];
    }
    if(n>1) m--;
    return m;
}
double rotating_calipers(Point *a,int n){
    int k=1;
    double ans=INF;
    a[n]=a[0];
    for (int i=0; i<n; i++){
        while (d_cmp(abs(XMulti(a[i],a[k+1],a[i+1]))-abs(XMulti(a[i],a[k],a[i+1])))==1)
            k=(k+1)%n;
//        ans=max(ans,max(dis2(a[i],a[k]),dis2(a[i+1],a[k]))); //旋转卡壳求凸包的直径，平面最远的点对
        ans=min(ans,DIS(a[i],a[k],a[i+1])); //旋转卡壳求凸包的最短投影长度
    }
    return ans;
}

int main(){
    int n,R;
    while (scanf("%d%d",&n,&R) != EOF){
        for(int i=0; i<n; i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        int m = ConvexHull(p,n,st);
        double ans = rotating_calipers(st,m);
        printf("%.10f\n",ans);
    }
    return 0;
}
/*
3
0 0
0 10
10 0

*/

