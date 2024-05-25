#include <bits/stdc++.h>

using namespace std;

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

int main()
{
    long long n;
    cin >> n;
    cout << eular(n);
    return 0;
}