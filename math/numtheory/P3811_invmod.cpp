#include <bits/stdc++.h>
#define int long long

using namespace std;
int inv[3000006];

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, p;
    cin >> n >> p;
    inv[1] = 1;
    cout << "1\n";
    for (int i = 2; i <= n; i++)
    {
        inv[i] = (p - p / i) * inv[p % i] % p;
        cout << inv[i] << "\n";
    }
    return 0;
}