const double PI = acos(-1.0);
const double eps = 1e-8;
const double INF = 1e18 + 11;

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
};
typedef Point Vector;
struct Circle{
    Point c;
    double r;
    Circle(){}
    Circle(Point c,double r):c(c),r(r) {}
    Point point(double a) { return Point(c.x + cos(a)*r, c.y + sin(a)*r); }
};
struct Line{
    Point p;
    Vector v;
    double ang;
    Line(){}
    Line(Point p, Vector v):p(p),v(v){ ang = atan2(v.y,v.x); }
    Point point(double t) { return Point(p.x + t*v.x, p.y + t*v.y); }
    bool operator < (const Line &L)const { return ang < L.ang; }
};
template <class T> T sqr(T x) { return x * x;}
Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }
double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
Vector VectorUnit(Vector x){ return x / Length(x);}
Vector Normal(Vector x) { return Point(-x.y, x.x) / Length(x);}
double angle(Vector v) { return atan2(v.y, v.x); }
bool OnSegment(Point P, Point A, Point B) {         //端点也算
    return d_cmp(Cross(A-P,B-P)) == 0 && d_cmp(Dot(A-P,B-P)) <= 0;
}
double DistanceToSeg(Point P, Point A, Point B) {
    if(A == B) return Length(P-A);
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if(d_cmp(Dot(v1, v2)) < 0) return Length(v2);
    if(d_cmp(Dot(v1, v3))>0) return Length(v3);
    return fabs(Cross(v1, v2)) / Length(v1);
}
double SegDistancetoSeg(Point A,Point B,Point C,Point D) {
    return min({DistanceToSeg(C,A,B),DistanceToSeg(D,A,B),DistanceToSeg(A,C,D),DistanceToSeg(B,C,D)});
}
double DistanceToLine(Point P, Point A, Point B) {
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1,v2)) / Length(v1);
}
Point GetLineIntersection(Line A, Line B) {
    Vector u = A.p - B.p;
    double t = Cross(B.v, u) / Cross(A.v, B.v);
    return A.p + A.v*t;
}
double DisP(Point A,Point B) {
    return Length(B-A);
}
bool SegmentIntersection(Point A,Point B,Point C,Point D) {
    return max(A.x,B.x) >= min(C.x,D.x) &&
           max(C.x,D.x) >= min(A.x,B.x) &&
           max(A.y,B.y) >= min(C.y,D.y) &&
           max(C.y,D.y) >= min(A.y,B.y) &&
           d_cmp(Cross(C-A,B-A)*Cross(D-A,B-A)) <= 0 &&
           d_cmp(Cross(A-C,D-C)*Cross(B-C,D-C)) <= 0;
}
bool LineSegmentIntersection(Point A,Point B,Point C,Point D) {
    return d_cmp(Cross(C-A,B-A)*Cross(D-A,B-A)) <= 0;
}
void SegIntersectionPoint(Point& P,Point a,Point b,Point c,Point d) {  //需保证ab,cd相交
    P.x = (Cross(d-a,b-a)*c.x - Cross(c-a,b-a)*d.x)/(Cross(d-a,b-a)-Cross(c-a,b-a));
    P.y = (Cross(d-a,b-a)*c.y - Cross(c-a,b-a)*d.y)/(Cross(d-a,b-a)-Cross(c-a,b-a));
}
Vector Rotate(Point P,Vector A,double rad){     //以P为基准点把向量A旋转rad
    return Vector(P.x+A.x*cos(rad)-A.y*sin(rad),P.y+A.x*sin(rad)+A.y*cos(rad));
}
//点是否在多边形内部（环顾法）
int CheckPointInPolygon(Point A,Point* p,int n){
    double TotalAngle = 0.0;
    for(int i=0;i<n;i++) {
        if(d_cmp(Cross(p[i]-A,p[(i+1)%n]-A)) >= 0) TotalAngle += Angle(p[i]-A,p[(i+1)%n]-A);
        else TotalAngle -= Angle(p[i]-A,p[(i+1)%n]-A);
    }
    if(d_cmp(TotalAngle) == 0)                 return 0;   //外部
    else if(d_cmp(fabs(TotalAngle)-2*PI) == 0) return 1;   //完全内部
    else if(d_cmp(fabs(TotalAngle)-PI) == 0)   return 2;   //边界上
    else                                      return 3;   //多边形顶点
}
//射线法
int Ray_PointInPolygon(Point A,Point* p,int n) {
    int wn = 0;
    for(int i=0;i<n;i++) {
        //if(OnSegment(A,p[i],p[(i+1)%n])) return -1;    //边界
        int k = d_cmp(Cross(p[(i+1)%n]-p[i], A-p[i]));
        int d1 = d_cmp(p[i].y-A.y);
        int d2 = d_cmp(p[(i+1)%n].y-A.y);
        if(k>0 && d1 <= 0 && d2>0) wn++;
        if(k < 0 && d2 <= 0 && d1>0) wn--;
    }
    if(wn) return 1;     //内部
    return 0;            //外部
}
//判断未知时针方向的多边形是否是凸包
bool CheckConvexHull(Point* p,int n){
    int dir = 0;   //旋转方向
    for(int i=0;i<n;i++) {
        int nowdir = d_cmp(Cross(p[(i+1)%n]-p[i],p[(i+2)%n]-p[i]));
        if(!dir) dir = nowdir;
        if(dir*nowdir < 0) return false;     //非凸包
    }
    return true;
}
//////凸包
int ConvexHull(Point* p, int n, Point* ch) {
    sort(p,p+n);
    int m = 0;
    for(int i=0;i<n;i++) {
        while(m>1&&Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i=n-2;i>=0;i--) {
        while(m>k&&Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n>1) m--;
    return m;
}
double CalcConvexArea(Point* p,int n) {        //凸包面积
    double area = 0.0;
    for(int i=1;i<n-1;i++)
        area += Cross(p[i]-p[0],p[i+1]-p[0]);
    return fabs(area*0.5);
}
double CalcConvexLength(Point* p,int n) {
    double Len = 0.0;
    for(int i=0;i<n;i++) Len += Length(p[(i+1)%n]-p[i]);
    return Len;
}
//////////旋转卡壳求凸包最远两点
double RotatingCalipers(Point* ch,int n) {  //旋转卡壳
    int p,q = 1;
    double ans = 0.0;
    ch[n] = ch[0];
    for(p=0;p<n;p++) {
        while(d_cmp(Cross(ch[p+1]-ch[p],ch[q+1]-ch[p])-Cross(ch[p+1]-ch[p],ch[q]-ch[p]))>0)
            q = (q+1)%n;
        ans = max(ans,max(DisP(ch[p],ch[q]),DisP(ch[p+1],ch[q+1])));
    }
    return ans*ans;
}
double MinDisOfTwoConvexHull(Point P[],int n,Point Q[],int m) {   //旋转卡壳求两个顺时针凸包的最近距离
    int Pymin = 0, Qymax = 0, i,j;
    for(i=0;i<n;i++) if(d_cmp(P[i].y-P[Pymin].y) < 0) Pymin = i;
    for(i=0;i<m;i++) if(d_cmp(Q[i].y-Q[Qymax].y)>0) Qymax = i;
    P[n] = P[0], Q[m] = Q[0];
    double Mindis = INF, Tmp;
    for(i=0;i<n;i++) {
        while(d_cmp(Tmp = Cross(P[Pymin+1]-P[Pymin],Q[Qymax+1]-P[Pymin])-Cross(P[Pymin+1]-P[Pymin],Q[Qymax]-P[Pymin]))>0)
            Qymax = (Qymax+1)%m;
        if(d_cmp(Tmp) < 0) Mindis = min(Mindis,DistanceToSeg(Q[Qymax],P[Pymin],P[Pymin+1]));
        else              Mindis = min(Mindis,SegDistancetoSeg(P[Pymin],P[Pymin+1],Q[Qymax],Q[Qymax+1]));
        Pymin = (Pymin+1)%n;
    }
    return Mindis;
}
bool OnLeft(Line L, Point p) { return d_cmp(Cross(L.v,p-L.p))>0; }
Point* p;
bool CmpPolarPoint(Point a,Point b) {     //点极角排序
    int d = d_cmp(Cross(a-p[0],b-p[0]));
    if(!d) return DisP(p[0],a) < DisP(p[0],b);
    return d>0;
}
bool CmpPolarLine(Line a,Line b) {        //直线极角排序
    return angle(a.v) < angle(b.v);
}
void GetL(bool counter,Point* p,int n,Line* L) {  //多边形的边转为直线
    if(counter) { for(int i=n-1;i>=0;i--) L[n-i-1] = Line(p[(i+1)%n],p[i]-p[(i+1)%n]); }
    else { for(int i=0;i<n;i++) L[i] = Line(p[i],p[(i+1)%n]-p[i]); }
}
int HalfPlaneIntersection(Line* L, int n, Point* poly) {    //半平面交点存入poly
    sort(L,L+n,CmpPolarLine);
    int first,last;
    Point *p = new Point[n];
    Line  *q = new Line[n];
    q[first=last=0] = L[0];
    for(int i=1;i<n;i++) {
        while(first < last&&!OnLeft(L[i],p[last-1])) last--;
        while(first < last&&!OnLeft(L[i],p[first]))  first++;
        q[++last] = L[i];
        if(d_cmp(Cross(q[last].v, q[last-1].v)) == 0) {
            last--;
            if(OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if(first < last) p[last-1] = GetLineIntersection(q[last-1],q[last]);
    }
    while(first < last&&!OnLeft(q[first],p[last-1])) last--;
    if(last-first <= 1) return 0;       //点或线或无界平面，返回0
    p[last] = GetLineIntersection(q[last],q[first]);
    int m = 0;
    for(int i=first;i<=last;i++) poly[m++] = p[i];
    delete p; delete q;
    return m;
}
int LineCrossPolygon(Point& L1,Point& L2,Point* p,int n,Point* poly) {  //直线(L1,L2)切割多边形p，形成新的多边形poly
    int m = 0;
    for(int i=0,j;i<n;i++) {
        if(d_cmp(Cross(L1-p[i],L2-p[i])) >= 0) { poly[m++] = p[i]; continue; }
        j = (i-1+n)%n;
        if(d_cmp(Cross(L1-p[j],L2-p[j]))>0) poly[m++] = GetLineIntersection(Line(L1,L2-L1),Line(p[j],p[i]-p[j]));
        j = (i+1+n)%n;
        if(d_cmp(Cross(L1-p[j],L2-p[j]))>0) poly[m++] = GetLineIntersection(Line(L1,L2-L1),Line(p[j],p[i]-p[j]));
    }
    return m;
}
//////圆
bool InCircle(Point x, Circle c) { return d_cmp(c.r - Length(c.c-x))>0; } //not in border
int GetCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) //return 交点个数
{
    double d = Length(C1.c - C2.c);
    if(d_cmp(d) == 0){
        if(d_cmp(C1.r - C2.r) == 0) return -1;  //两圆重合
        return 0;
    }
    if(d_cmp(C1.r + C2.r - d) < 0) return 0;
    if(d_cmp(fabs(C1.r - C2.r) - d)>0) return 0;

    double a = angle(C2.c - C1.c);             //向量C1C2的极角
    double da = acos((sqr(C1.r) + sqr(d) - sqr(C2.r)) / (2*C1.r*d)); //C1C2到C1P1的极角

    Point p1 = C1.point(a-da), p2 = C1.point(a+da);
    sol.push_back(p1);
    if(p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}
int GetSegCircleIntersection(Line L, Circle C, Point* sol)
{
    Vector Noml = Normal(L.v);
    Line PL = Line(C.c, Noml);
    Point IP = GetLineIntersection(PL, L); //弦的中点
    double Dis = Length(IP - C.c);
    if(d_cmp(Dis-C.r)>0) return 0;        //在圆外
    Vector HalfChord = VectorUnit(L.v)*sqrt(sqr(C.r)-sqr(Dis));
    int ind = 0;
    sol[ind] = IP + HalfChord;
    if(OnSegment(sol[ind],L.p,L.point(1))) ind++;
    sol[ind] = IP - HalfChord;
    if(OnSegment(sol[ind],L.p,L.point(1))) ind++;
    return ind;
}

Point Zero = Point(0,0);
double TriAngleCircleInsection(Circle C, Point A, Point B)
{
    Vector OA = A-C.c, OB = B-C.c;
    Vector BA = A-B, BC = C.c-B;
    Vector AB = B-A, AC = C.c-A;
    double DOA = Length(OA), DOB = Length(OB),DAB = Length(AB), r = C.r;
    if(d_cmp(Cross(OA,OB)) == 0) return 0;
    if(d_cmp(DOA-C.r) < 0&&d_cmp(DOB-C.r) < 0) return Cross(OA,OB)*0.5;
    else if(DOB < r&&DOA >= r) {
        double x = (Dot(BA,BC) + sqrt(r*r*DAB*DAB-Cross(BA,BC)*Cross(BA,BC)))/DAB;
        double TS = Cross(OA,OB)*0.5;
        return asin(TS*(1-x/DAB)*2/r/DOA)*r*r*0.5+TS*x/DAB;
    }
    else if(DOB >= r&&DOA < r) {
        double y = (Dot(AB,AC)+sqrt(r*r*DAB*DAB-Cross(AB,AC)*Cross(AB,AC)))/DAB;
        double TS = Cross(OA,OB)*0.5;
        return asin(TS*(1-y/DAB)*2/r/DOB)*r*r*0.5+TS*y/DAB;
    }
    else if(fabs(Cross(OA,OB)) >= r*DAB || Dot(AB,AC) <= 0 || Dot(BA,BC) <= 0) {
        if(Dot(OA,OB) < 0) {
            if(Cross(OA,OB) < 0) return (-acos(-1.0)-asin(Cross(OA,OB)/DOA/DOB))*r*r*0.5;
            else                 return ( acos(-1.0)-asin(Cross(OA,OB)/DOA/DOB))*r*r*0.5;
        }
        else                     return asin(Cross(OA,OB)/DOA/DOB)*r*r*0.5;
    }
    else {
        double x = (Dot(BA,BC)+sqrt(r*r*DAB*DAB-Cross(BA,BC)*Cross(BA,BC)))/DAB;
        double y = (Dot(AB,AC)+sqrt(r*r*DAB*DAB-Cross(AB,AC)*Cross(AB,AC)))/DAB;
        double TS = Cross(OA,OB)*0.5;
        return (asin(TS*(1-x/DAB)*2/r/DOA)+asin(TS*(1-y/DAB)*2/r/DOB))*r*r*0.5 + TS*((x+y)/DAB-1);
    }
}
