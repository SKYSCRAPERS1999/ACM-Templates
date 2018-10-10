inline void input(__int128 &s) {
    s = 0;
    char c = ' ';
    while (c > '9' || c < '0') c = getchar();
    while (c >= '0' && c <= '9') {
        s = s * 10 + c - '0';
        c = getchar();
    }
}
inline void output(__int128 x) {
    if (x > 9) output(x / 10);
    putchar(x % 10 + '0');
}
