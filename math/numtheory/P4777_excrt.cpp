#include <bits/stdc++.h>

using ll = __int128;
using namespace std;

int n;
ll ai[100005], bi[100005];

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    // ax+by=gcd(a,b)
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    auto g = exgcd(b, a % b, x, y);
    auto tmp = x;
    x = y;
    y = tmp - (a / b) * y;
    return g;
}

ll excrt()
{
    // 拓展中国剩余定理
    __int128_t x, y, k;
    __int128_t M = bi[1], ans = ai[1]; // 第一个方程的特解
    for (int i = 2; i <= n; ++i)
    {
        ll a = M, b = bi[i], c = (ai[i] - ans % b + b) % b;
        ll d = exgcd(a, b, x, y);
        ll bg = b / d; // lcm
        if (c % d != 0)
            return -1; // 判断是否无解，然而这题其实不用
        x = x * (c / d);
        x %= bg;
        ans += x * M; // 更新前k个方程组的答案
        M *= bg;      // M为前k个m的lcm
        ans = (ans % M + M) % M;
    }
    ans = (ans % M + M) % M;
    return ans;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        long long b, a;
        cin >> b >> a;
        bi[i] = b;
        ai[i] = a;
    }
    cout << (long long)excrt();
    return 0;
}