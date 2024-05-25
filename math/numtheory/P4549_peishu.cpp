#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main()
{
    int n;
    cin >> n;
    int ans = 0, x;
    while (n--)
    {
        cin >> x;
        if (ans == 0)
            ans = x;
        else
            ans = __gcd(ans, x);
    }
    cout << abs(ans);
    return 0;
}