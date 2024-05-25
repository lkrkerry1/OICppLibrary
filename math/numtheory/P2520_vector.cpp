#include <bits/stdc++.h>
#define int long long

using namespace std;

bool check(int a, int b, int d)
{
    return (a % d == 0) && (b % d == 0);
}

signed main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        a = abs(a);
        b = abs(b);
        x = abs(x);
        y = abs(y);
        int d = __gcd(2 * a, 2 * b);
        a %= d;
        b %= d;
        x %= d;
        y %= d;
        if (check(x + a, y + b, d) || check(x, y, d) || check(x + a + b, y + a + b, d) || check(x + b, y + a, d))
        {
            cout << "Y\n";
            continue;
        }
        cout << "N\n";
    }
    return 0;
}