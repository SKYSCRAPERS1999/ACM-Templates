#include <bits/stdc++.h>
#define bp __builtin_popcountll
#define pb push_back
#define in(s) freopen(s, "r", stdin);
#define inout(s, end1, end2) freopen((string(s) + "." + end1).c_str(), "r", stdin),\
		freopen((string(s) + "." + end2).c_str(), "w", stdout);
#define fi first
#define se second
#define bw(i, r, l) for (int i = r - 1; i >= l; i--)
#define fw(i, l, r) for (int i = l; i < r; i++)
#define fa(i, x) for (auto i: x)
using namespace std;
const double PI = acos(-1);
const int mod = 1e9 + 7, inf = 1061109567;
const long long infll = 4557430888798830399;
const int N = 1005;
typedef complex<double> base;
base omega(int i, int n) {
	double angle = 2 * PI / n;
	return base(cos(angle * i), sin(angle * i));
}
struct FFT {
	vector<base> fft(vector<base> &v, base w) {
		int n = v.size();
		if (n == 1) return v;
		vector<base> even(n / 2), odd(n / 2);
		fw (i, 0, v.size()) {
			if (i & 1) odd[i >> 1] = v[i];
			else even[i >> 1] = v[i];
		}
		vector<base> fo = fft(odd, w * w), fe = fft(even, w * w);
		vector<base> fv;
		fv.resize(n);
		base cur = 1;
		fw (i, 0, n / 2) {
			base tmpe = fe[i], tmpo = cur * fo[i];
			fv[i] = tmpe + tmpo;
			fv[i + n / 2] = tmpe - tmpo;
			cur *= w;
		}
		return fv;
	}
	vector<int> mul(vector<int> &_a, vector<int> &_b, int sz) {
		vector<base> a(_a.begin(), _a.end()), b(_b.begin(), _b.end());
		a.resize(sz), b.resize(sz);
		base tmp = omega(1, sz);
		vector<base> fa = fft(a, tmp), fb = fft(b, tmp);
		vector<base> fv(sz);
		fw (i, 0, sz) fv[i] = conj(fa[i] * fb[i]);
		fv = fft(fv, tmp);
		vector<int> ans(sz);
		fw (i, 0, sz) {
			int tmp = (int)(fv[i].real() / sz + 0.5);
			if (tmp > 0) ans[i] = 1;
			else ans[i] = 0;
		}
		return ans;
	}
} f;
int n, k, a[N], mxa = 0;
vector<int> fpow(vector<int> &a, int p) {
	if (p == 1) return a;
	//The maximal weight for p is mxa * p, so find the appropriate sz
	int tmp = mxa * p, sz = 1;
	while (sz <= mxa * p) sz <<= 1;
	vector<int> ans = fpow(a, p >> 1);
	ans = f.mul(ans, ans, sz);
	if (p & 1) ans = f.mul(ans, a, sz);
	return ans;
}
signed main() {
	#ifdef BLU
	in("blu.inp");
	#endif
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	fw (i, 0, n) cin >> a[i], mxa = max(mxa, a[i]);
	//Answer for k = 1 can be found. Then it's just this polynomial powered by k. Use FFT.
	vector<int> og(1001, 0);
	fw (i, 0, n) og[a[i]] = 1;
	vector<int> ans = fpow(og, k);
	fw (i, 1, ans.size()) if (ans[i]) cout << i << " ";
	return 0;
}
