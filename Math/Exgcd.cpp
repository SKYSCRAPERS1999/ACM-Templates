//exgcd
void ex_gcd(int &d, int a, int b, int &x, int &y){
    if (b ==0) {d = a; x = 1; y = 0; return;}
    else {ex_gcd(d, b, a % b, y, x); y -= x*(a/b);}
}
//get inv
const int MOD = 1e9 + 7;
int inverse(int a) {
	return a == 1 ? 1 : (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}
