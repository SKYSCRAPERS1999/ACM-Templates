import java.util.*;
import java.math.*;
import java.io.*;
public class Main {
Scanner cin = new Scanner(new BufferedInputStream(System.in));
public class Complex{
double real, imag;
Complex(double a, double b){
this.real = a; this.imag = b;
}
void set(double a, double b) {
this.real = a; this.imag = b;
}
Complex add(Complex rhs) {
double a = this.real + rhs.real;
double b = this.imag + rhs.imag;
return new Complex(a, b);
}
Complex subtract(Complex rhs) {
double a = this.real - rhs.real;
double b = this.imag - rhs.imag;
return new Complex(a, b);
}
Complex multiply(Complex rhs) {
double a = this.real * rhs.real - this.imag * rhs.imag;
double b = this.real * rhs.imag + this.imag * rhs.real;
return new Complex(a, b);
}
Complex divide(Complex rhs) {
Complex c = new Complex(this.real, this.imag).multiply(new Complex(rhs.real, -rhs.imag));
double div = rhs.real * rhs.real + rhs.imag * rhs.imag;
c.set(c.real / div, c.imag / div);
return c;
}
}	
int N, M, logM;
double PI = Math.acos(-1.0);
Complex [] A, B, C;
int [] BitReverse(int [] X) {
for (int i = 0; i < M; i++)
{
int tmp = X[i], cur = 0;
for (int j = 0; j < logM; j++, tmp >>= 1) cur = (cur << 1) | (tmp & 1);
X[i] = cur;
}
return X;
}

Complex [] FFT(Complex [] X, int [] P, int dir) {
Complex [] XX = X.clone();
if (dir == 1) {
for (int i = 0; i < M; i++) X[i] = XX[P[i]];
}else {
for (int i = 0; i < M; i++) X[P[i]] = XX[i];
}
for (int s = 1, m = 1; s <= logM; s++) {
m <<= 1;
Complex wm = new Complex(Math.cos(2*PI/m), dir * Math.sin(2*PI/m));
for (int k = 0; k < M; k += m) {
Complex w = new Complex(1.0, 0);
for (int j = 0; j < (m >> 1); j++) {
Complex u = X[k + j], t = X[k + j + m / 2].multiply(w);
X[k + j] = u.add(t);
X[k + j + m / 2] = u.subtract(t);
w = w.multiply(wm);
}
}
}
return X;
}

void Iter_FFT() {
int [] P = new int[M]; for (int i = 0; i < M; i++) P[i] = i;
P = BitReverse(P);
A = FFT(A, P, 1); B = FFT(B, P, 1);
for (int i = 0; i < M; i++) C[i] = A[i].multiply(B[i]);
C = FFT(C, P, -1);
for (int i = 0; i < M; i++) C[i].set(C[i].real / M, C[i].imag / M);
}

void run() {
N = cin.nextInt();
for (M = 1, logM = 0; M < 2 * N; M <<= 1, logM++);
A = new Complex[M];
B = new Complex[M];
C = new Complex[M];
for (int i = 0; i < M; i++) {A[i] = new Complex(0.0, 0.0); B[i] = new Complex(0.0, 0.0);}
for (int i = 0; i < N; i++) {A[i].set(1.0, 0.0); B[i].set(1.0, 0.0);}
Iter_FFT();

for (int i = 0; i < M; i++) System.out.print((int)(C[i].real + 0.5) + " ");
System.out.println();

}
public static void main(String[] args) {
new Main().run();
}
}

