
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
            // make a self-running function that build one layer of the tree
            if (l + 1 == r)
            {
                // contain only one node
                value[x] = init[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, this->ls(x), l, m);
            self(self, this->rs(x), m, r);                      // build the tree recursively
            value[x] = value[this->ls(x)] + value[this->rs(x)]; // "sum" up the value
        };
        build(build, 0, 0, n); // start from beginning
    }
};

#include <bits/stdc++.h>

using namespace std;

struct l
{
    bool x;
    l(bool x = 0) : x(x){};
    l operator+=(const l &other)
    {
        x ^= other.x;
        return *this;
    }
};

struct v
{
    long long x, s;
    v(long long x = 0, long long s = 1) : x(x), s(s){};
    v operator+=(const l &other)
    {
        if (other.x == 0)
        {
            return *this;
        }
        else
        {
            x = s - x;
            return *this;
        }
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
    auto lst = LazySegmentTree<v, l>(n);
    for (int i = 1; i <= m; i++)
    {
        int op, a, b;
        cin >> op >> a >> b;
        if (op)
        {
            cout << lst.get(a - 1, b).x << "\n";
        }
        else
        {
            lst.set(a - 1, b, 1);
        }
    }
    return 0;
}
