#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int a1, a0, b1, b0;
        cin >> a0 >> a1 >> b0 >> b1;
        int b2 = b1 / b0;
        int a2 = a0 / a1;
        int ans = 0;
        for (int m = 1; m * m <= b1; m++)
        {
            if (b1 % m == 0)
            {
                if (m % a1 == 0 && __gcd(m / a1, a2) == 1 && __gcd(b1 / m, b2) == 1)
                {
                    ans++;
                }
                int m2 = b1 / m;
                if (m == m2)
                    continue;
                if (m2 % a1 == 0 && __gcd(m2 / a1, a2) == 1 && __gcd(b1 / m2, b2) == 1)
                {
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}