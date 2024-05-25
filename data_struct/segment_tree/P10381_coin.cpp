#include <vector>
#include <cassert>

template <typename Value, typename Lazy>
class LazySegmentTree
{
    // Lazy: operator +=
    // Value: operator += +
    int n;
    std::vector<Value> value;
    std::vector<Lazy> lazy;

    constexpr inline int ls(const int x) { return x * 2 + 1; }
    constexpr inline int rs(const int x) { return x * 2 + 2; }

    constexpr void push_down(const int x)
    {
        value[ls(x)] += lazy[x]; // add(acatually need to add all the sons)
        value[rs(x)] += lazy[x];
        lazy[ls(x)] += lazy[x]; // push down
        lazy[rs(x)] += lazy[x];
        lazy[x] = Lazy(); // reset the lazy tag
    }

    void set(const int x, const int l, const int r, const int L, const int R, const Lazy &K)
    {
        if (L <= l && r <= R)
        {
            lazy[x] += K;
            value[x] += K;
            return;
        }
        int m = (l + r) / 2;
        push_down(x);
        if (L < m)
            set(ls(x), l, m, L, R, K);
        if (R > m)
            set(rs(x), m, r, L, R, K);
        value[x] = value[ls(x)] + value[rs(x)]; // update
    }
    Value get(const int x, const int l, const int r, const int L, const int R)
    {
        if (L <= l && r <= R)
            return value[x];
        int m = (l + r) / 2;
        push_down(x);
        if (R <= m)
            return get(ls(x), l, m, L, R);
        if (L >= m)
            return get(rs(x), m, r, L, R);
        return get(ls(x), l, m, L, R) + get(rs(x), m, r, L, R);
    }

public:
    void set(const int l, const int r, const Lazy &k) { set(0, 0, n, l, r, k); }
    void set(const int p, const Lazy &k) { set(p, p + 1, k); }
    void set(const Lazy &k) { value[0] += k, lazy[0] += k; }
    Value get(const int l, const int r) { return get(0, 0, n, l, r); }
    Value get(const int p) { return get(p, p + 1); }
    Value get() { return value[0]; }

    LazySegmentTree(const int n)
        : LazySegmentTree(n, std::vector<Value>(n)) {}
    LazySegmentTree(const int n, std::vector<Value> init)
        : n(n), value(n * 4), lazy(n * 4)
    {
        assert(init.size() == n);
        auto build = [&](auto self, const int x, const int l, const int r)
        {
            if (l + 1 == r)
            {
                value[x] = init[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, this->ls(x), l, m), self(self, this->rs(x), m, r);
            value[x] = value[this->ls(x)] + value[this->rs(x)];
        };
        build(build, 0, 0, n);
    }
};

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
        x += rhs.x; // add all the son elements to current position
        return *this;
    }
};

v operator+(const v &lhs, const v &rhs)
{
    return v(max(lhs.x, rhs.x), lhs.s + rhs.s);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        vector<long long> a(n);
        vector<long long> f(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        auto lst = LazySegmentTree<v, l>(n);
        for (int i = n - 1; i >= 0; i--)
        {
            f[i] = max(a[i], lst.get(i, min(i + a[i] + 1, n)).x);
            lst.set(i, f[i]);
            if (i + 1 < n)
                lst.set(i + 1, n, a[i]);
        }
        cout << f[0] << "\n";
    }
    return 0;
}