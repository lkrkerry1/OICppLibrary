#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        a--;
        int ans = 0;
        for (int l = 1, r = 1; l <= a; l = r + 1)
        {
            r = a / (a / l);
            ans -= (r - l + 1) * (a / l);
        }
        for (int l = 1, r = 1; l <= b; l = r + 1)
        {
            r = b / (b / l);
            ans += (r - l + 1) * (b / l);
        }
        cout << ans << endl;
    }
    return 0;
}