int read() {
    int num = 0; char c; bool flag = false;
    while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
    if (c == '-') flag = true;
    else num = c - '0';
    while (isdigit(c = getchar())) num = num * 10 + c - '0';
    return (flag ? -1 : 1) * num;
}
