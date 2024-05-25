#include <bits/stdc++.h>
#define int long long

using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y)
{
    // ax+by=gcd(a,b)
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long g = exgcd(b, a % b, x, y);
    auto tmp = x;
    x = y;
    y = tmp - (a / b) * y;
    return g;
}

signed main()
{
    int a, b, x, y;
    cin >> a >> b;
    exgcd(a, b, x, y);
    cout << ((x % b) + b) % b;
    return 0;
}