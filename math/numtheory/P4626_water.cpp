#include <bits/stdc++.h>

using namespace std;
const int mod = 100000007;
bool s[100000007];
int prime[5761460];

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

int main()
{
    int n;
    cin >> n;
    int cnt = 0;
    for (int i = 2; i <= n; i++)
    {
        if (!s[i])
            prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (prime[j] * i > n)
                break;
            s[prime[j] * i] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    long long ans = 1;
    for (int i = 1; i <= cnt; i++)
    {
        ans *= (bfpow(prime[i], log2(n) / log2(prime[i]), mod));
        ans %= mod;
    }
    cout << ans;
    return 0;
}