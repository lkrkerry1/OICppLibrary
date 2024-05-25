#include <bits/stdc++.h>
#define int long long

using namespace std;

int bckt[100005];

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    int ans = n * k;
    for (int l = 1, r = 1; l <= n; l = r + 1)
    {
        int t = k / l;
        r = n;
        if (t)
        {
            r = min(k / t, r);
        }
        ans -= ((r - l + 1) * t) * (l + r) / 2;
    }
    cout << ans;
    return 0;
}