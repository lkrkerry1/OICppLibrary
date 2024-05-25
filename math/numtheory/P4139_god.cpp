#include <bits/stdc++.h>

using namespace std;

int eular[10000005];
bool s[10000005];
vector<int> prime;

void initEular()
{
    int n = 1e7 + 5;
    eular[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!s[i])
        {
            prime.push_back(i);
            eular[i] = i - 1;
        }
        for (auto p : prime)
        {
            if (p * i > n)
                break;
            s[p * i] = 1;

            if (i % p == 0)
            {
                eular[i * p] = eular[i] * p;
                break;
            }
            else
            {
                eular[i * p] = eular[i] * (p - 1);
            }
        }
    }
}

long long bfpow(long long a, long long b, long long p)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

int recursev(int x)
{
    if (x == 1 || x == 0)
        return 0;
    return bfpow(2, recursev(eular[x]) + eular[x], x);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    initEular();
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        cout << recursev(n) << "\n";
    }
    return 0;
}