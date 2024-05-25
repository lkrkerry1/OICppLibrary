#include "SegmentTree.hpp"

#include <bits/stdc++.h>

using namespace std;

struct l
{
    long long x;
    l(long long x = 0) : x(x){};
    l operator+=(const l &rhs)
    {
        x += rhs.x;
        return *this;
    }
};

struct v
{
    long long x, s;
    v(long long x = 0, long long s = 1) : x(x), s(s){};
    v operator+=(const l &rhs)
    {
        x += (rhs.x * s); // add all the son elements to current position
        return *this;
    }
};

v operator+(const v &lhs, const v &rhs)
{
    return v(lhs.x + rhs.x, lhs.s + rhs.s);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<v> a(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a[i] = v(x);
    }
    auto lst = LazySegmentTree<v, l>(n, a);
    for (int i = 0; i < m; i++)
    {
        int op, x, y, k;
        cin >> op >> x >> y;
        if (op == 1)
        {
            cin >> k;
            lst.set(x - 1, y, k);
        }
        else
        {
            cout << lst.get(x - 1, y).x << "\n";
        }
    }
}