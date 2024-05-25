#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int m;
    cin >> m;
    while (m--)
    {
        int x, z;
        cin >> x >> z;
        int y2, gc;
        if (z % x)
        {
            cout << "-1\n";
            continue;
        }
        y2 = z / x;
        while (gc = __gcd(y2, x) != 1)
        {
            y2 = x * gc;
        }
        cout << y2 << "\n";
    }
    return 0;
}