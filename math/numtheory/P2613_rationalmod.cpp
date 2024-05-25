#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MOD = 19260817; // MOD是题解中的"p"
inline int getint()
{
    int res = 0, ch = getchar();
    while (!isdigit(ch) and ch != EOF)
        ch = getchar();
    while (isdigit(ch))
    {
        res = (res << 3) + (res << 1) + (ch - '0');
        res %= MOD; // 直接对MOD取余
        ch = getchar();
    }
    return res;
}

long long bfpow(long long a, long long b, long long p)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

signed main()
{
    int m = getint();
    int n = getint();
    int inv = bfpow(n, MOD - 2, MOD);
    cout << (m * inv) % MOD;
    return 0;
}