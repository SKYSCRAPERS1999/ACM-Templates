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
int upper_bound(BigInteger x, int low, int high, BigInteger [] a) {
int left = low, right = high;
while (left < right) {
int mid = left + (right - left) / 2;
if (a[mid].compareTo(x) != 1) {
left = mid + 1;
}else { right = mid; }
}
return left;
}
