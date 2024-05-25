#include <bits/stdc++.h>

using namespace std;
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
long long eular(long long n)
{
    long long ans = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            ans = (ans / i * (i - 1));
        }
        while (n % i == 0)
            n /= i;
    }
    if (n > 1)
    { // 还有其他质因数
        ans = (ans / n * (n - 1));
    }
    return ans;
}
int exeular(int a, int m)
{
    int phi = eular(m);
    char ch;
    int b = 0;
    bool flag = false;
    while (!isdigit(ch = getchar()))
        ;
    for (; isdigit(ch); ch = getchar())
    {
        b = (b << 3) + (b << 1) + (ch - '0');
        if (b > phi)
        {
            flag = true;
            b %= phi;
        }
    }
    if (flag)
    {
        b += phi;
    }
    return bfpow(a, b, m);
}
int main()
{
    int a, m, b;
    cin >> a >> m;
    cout << exeular(a, m);
    return 0;
}