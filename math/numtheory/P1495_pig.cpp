#include <bits/stdc++.h>
#define int __int128_t

using namespace std;

int a[100005];
int m[100005];

int exgcd(int a, int b, int &x, int &y)
{
    // ax+by=gcd(a,b)
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int g = exgcd(b, a % b, x, y);
    auto tmp = x;
    x = y;
    y = tmp - (a / b) * y;
    return g;
}
int inv(int a, int b)
{
    int x, y;
    exgcd(a, b, x, y);
    return ((x % b) + b) % b;
}
void write(int need_print)
{
    if (need_print < 0)
    {
        need_print = -need_print;
        putchar('-');
    }
    if (need_print > 9)
        write(need_print / 10);
    putchar(need_print % 10 + '0');
}
signed main()
{
    int n, M = 1;
    long long n2;
    cin >> n2;
    n = n2;
    for (signed i = 1; i <= n; i++)
    {
        long long m2, a2;
        cin >> m2 >> a2;
        m[i] = m2;
        a[i] = a2;
        M *= m[i];
    }
    int x = 0;
    for (signed i = 1; i <= n; i++)
    {
        int Mi = M / m[i];
        x += (a[i] * Mi * inv(Mi, m[i]));
    }
    write((x + M) % M);
    return 0;
}