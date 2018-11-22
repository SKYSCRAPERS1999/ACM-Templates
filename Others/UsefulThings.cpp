int: 1e9+7,1e9+9,233,19260817,19660813,19990129
long long: 951970612352230049,963284339889659609,1048364250160580293,1045571042176595707
compiler settings: -fsanitize=undefined
linker settings/other linker options: -lubsan

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); //mt19937_64 for 64-bits

bool Finish_read;
template<class T>inline void read(T &x) {Finish_read = 0; x = 0; int f =1; char ch = getchar(); while(!isdigit(ch)) {if(ch == '-')f = -1; if(ch == EOF)return; ch = getchar();} while(isdigit(ch))x = x * 10 + ch - '0', ch = getchar(); x *= f; Finish_read = 1;}
