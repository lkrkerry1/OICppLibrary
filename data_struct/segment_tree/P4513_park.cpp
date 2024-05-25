#include <vector>
template <typename Value>
class SegmentTree
{
    int n;
    std::vector<Value> value;

    constexpr inline int ls(const int x) { return x * 2 + 1; }
    constexpr inline int rs(const int x) { return x * 2 + 2; }

    void set(const int x, const int l, const int r, const int P, const Value &V)
    {
        if (l + 1 == r)
            return value[x] = V, void();
        int m = (l + r) / 2;
        if (P < m)
            set(ls(x), l, m, P, V);
        else
            set(rs(x), m, r, P, V);
        value[x] = value[ls(x)] + value[rs(x)];
    }
    Value get(const int x, const int l, const int r, const int L, const int R)
    {
        if (L <= l && r <= R)
            return value[x];
        int m = (l + r) / 2;
        if (R <= m)
            return get(ls(x), l, m, L, R);
        if (L >= m)
            return get(rs(x), m, r, L, R);
        return get(ls(x), l, m, L, R) + get(rs(x), m, r, L, R);
    }

public:
    void set(const int p, const Value &k) { set(0, 0, n, p, k); }
    Value get(const int l, const int r) { return get(0, 0, n, l, r); }
    Value get(const int p) { return get(p, p + 1); }
    Value get() { return value[0]; }

    SegmentTree(const int n)
        : n(n), value(n * 4)
    {
        std::vector<Value> init(n, Value());
        auto build = [&](auto self, const int x, const int l, const int r)
        {
            if (l + 1 == r)
                return value[x] = init[l], void();
            int m = (l + r) / 2;
            self(self, this->ls(x), l, m), self(self, this->rs(x), m, r);
            value[x] = value[this->ls(x)] + value[this->rs(x)];
        };
        build(build, 0, 0, n);
    }
    SegmentTree(const int n, const std::vector<Value> &init)
        : n(n), value(n * 4)
    {
        auto build = [&](auto self, const int x, const int l, const int r)
        {
            if (l + 1 == r)
            {
                value[x] = Value(init[l]);
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

const int imax = 1e4;

using namespace std;
struct v
{
    int max_segsum, sum, premax, sufmax;
    v(int sum = 0, int max_segsum = -imax, int premax = -imax, int sufmax = -imax)
        : sum(sum), max_segsum(max_segsum), premax(premax), sufmax(sufmax) {}
};

v operator+(const v &lhs, const v &rhs)
{
    auto result = v(lhs.sum + rhs.sum);
    result.premax = max(lhs.premax, lhs.sum + rhs.premax);
    result.sufmax = max(rhs.sufmax, lhs.sufmax + rhs.sum);
    result.max_segsum = max({rhs.max_segsum, lhs.max_segsum, rhs.premax + lhs.sufmax});
    // Note: max_segsum, not others(e.g. premax,sufmax)
    return result;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<v> a;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        a.emplace_back(v(x, x, x, x));
    }
    auto lst = SegmentTree<v>(n, a);
    for (int i = 0; i < m; i++)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 2)
        {
            lst.set(x - 1, v(y, y, y, y));
        }
        else
        {
            if (x >= y)
                swap(x, y);
            cout << lst.get(x - 1, y).max_segsum << "\n";
        }
    }
}