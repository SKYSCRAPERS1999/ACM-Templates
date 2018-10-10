import java.util.*;
import java.math.*;
import java.io.*;
public class Main {
Scanner cin = new Scanner(new BufferedInputStream(System.in));
BigInteger [][] A = new BigInteger[2][2];

BigInteger [][] mul(BigInteger [][] a, BigInteger [][] b){
int size = a.length;
BigInteger [][] c = new BigInteger[size][size];
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
c[i][j] = BigInteger.ZERO;
}
}
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
for (int k = 0; k < size; k++) {
c[i][j] = c[i][j].add(a[i][k].multiply(b[k][j]));
}
}
}
return c;				
}

BigInteger [][] qpow(BigInteger [][] a, int n){
int size = a.length;
BigInteger [][] res = new BigInteger [size][size];
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
res[i][j] = (i == j) ? BigInteger.ONE : BigInteger.ZERO;
}
}
while (n > 0) {
if ((n & 1) == 1) {
res = mul(res, a);
}
a = mul(a, a);
n >>= 1;
}
return res;
}

void run() {
A[0][0] = A[0][1] = A[1][0] = BigInteger.ONE; 
A[1][1] = BigInteger.ZERO;
System.out.println(qpow(A, 10)[0][0]);
}

public static void main(String[] args) {
	new Main().run();
}
}

