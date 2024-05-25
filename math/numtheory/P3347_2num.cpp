#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long a, b;
        cin >> a >> b;
        long long gv = __gcd(a, b);
        if (1ll << (int)log2(gv) != gv)
        {
            cout << "N\n";
        }
        else
        {
            cout << "Y\n";
        }
    }
    return 0;
}