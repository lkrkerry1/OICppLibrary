#include <bits/stdc++.h>
#define int long long

using namespace std;

int exgcd(int a, int b, int &x1, int &y1)
{
    if (!b)
    {
        x1 = 1;
        y1 = 0;
        return a;
    }
    int ans = exgcd(b, a % b, x1, y1);
    int t = x1;
    x1 = y1;
    y1 = t - a / b * y1;
    return ans;
}
signed main()
{
    int x, y, m, n, l;
    cin >> x >> y >> m >> n >> l;
    int a = x - y, b = n - m;
    if (b < 0)
    {
        a = -a;
        b = -b;
    }
    int k, bv;
    int g = exgcd(b, l, k, bv);
    if (a % g)
    {
        cout << "Impossible";
        return 0;
    }
    cout << ((k * (a / g)) % (l / g) + (l / g)) % (l / g);
    return 0;
}