import java.util.*;
import java.io.*;
import java.math.*;
public class G {
	Scanner cin = new Scanner(new BufferedInputStream(System.in));
	Set<BigInteger> ans = new TreeSet<>();
	BigInteger [] res = new BigInteger[10000];
	int n = 0;

	BigInteger [][] A = new BigInteger[2][2];
	BigInteger [][] B = new BigInteger[2][2];
	BigInteger lim = new BigInteger("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");	

	int lower_bound(BigInteger x, int low, int high, BigInteger [] a) {
		int left = low, right = high;
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (a[mid].compareTo(x) == -1) {
				left = mid + 1;
			}else { right = mid; }
		}
		return left;
	}
	void run() {
		A[0][0] = BigInteger.valueOf(0); A[0][1] = BigInteger.valueOf(1); A[1][0] = BigInteger.valueOf(-1); A[1][1] = BigInteger.valueOf(6);
		B[0][0] = BigInteger.valueOf(0); B[0][1] = BigInteger.valueOf(1); B[1][0] = BigInteger.valueOf(-1); B[1][1] = BigInteger.valueOf(14);
		BigInteger n0 = BigInteger.valueOf(0), n1 = BigInteger.valueOf(2);
		while (true) {
			ans.add(n0);
			BigInteger _n0 = A[0][0].multiply(n0).add(A[0][1].multiply(n1));
			BigInteger _n1 = A[1][0].multiply(n0).add(A[1][1].multiply(n1));
			n0 = _n0; n1 = _n1;
			if (n0.compareTo(lim) > 0) break;
		}
		n0 = BigInteger.valueOf(0); n1 = BigInteger.valueOf(6);
		while (true) {
			ans.add(n0);
			BigInteger _n0 = B[0][0].multiply(n0).add(B[0][1].multiply(n1));
			BigInteger _n1 = B[1][0].multiply(n0).add(B[1][1].multiply(n1));
			n0 = _n0; n1 = _n1;
			if (n0.compareTo(lim) > 0) break;
		}
		for (BigInteger v : ans) {
		     res[n++] = v;
		} 
		while (cin.hasNext()) {
			BigInteger m = cin.nextBigInteger();
			int l = lower_bound(m, 0, n - 1, res);
			System.out.println(res[l]);
		}
	}

	public static void main(String[] args) {
		new G().run();
	}

}

