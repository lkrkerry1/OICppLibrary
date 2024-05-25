#pragma once

#include <vector>
#include <cassert>

template <typename Value, typename Lazy>
class LazySegmentTree
{
    /*
     * LazySegmentTree: a class for segment tree with lazy tag*/
    // Lazy: operator +=
    // Value: operator += +
    int n; // length
    std::vector<Value> value; // values
    std::vector<Lazy> lazy; // lazy tags

    // left and right son values
    constexpr inline int ls(const int x) { return x * 2 + 1; }
    constexpr inline int rs(const int x) { return x * 2 + 2; }

    constexpr void push_down(const int x)
    {
        /*
         * pushdown the lazy tag*/
        value[ls(x)] += lazy[x]; // add(acatually need to add all the sons)
        value[rs(x)] += lazy[x];
        lazy[ls(x)] += lazy[x]; // push down
        lazy[rs(x)] += lazy[x];
        lazy[x] = Lazy(); // reset the lazy tag
    }

    void set(const int x, const int l, const int r, const int L, const int R, const Lazy &K)
    {
        /*
         * current index is [l,r)
         * trying to add each in [L,R) with K*/
        if (L <= l && r <= R)
        {
            /*
             * ----------------
             * L          R
             * l       r*/
            lazy[x] += K;
            value[x] += K;
            return;
        }
        int m = (l + r) / 2;
        push_down(x); // update value x
        if (L < m){
            /*
             * ----------------
             * L          R
             * l    m    r
             * ------*/
            set(ls(x), l, m, L, R, K);
        }
        if (R > m) // same above
            set(rs(x), m, r, L, R, K);
        value[x] = value[ls(x)] + value[rs(x)]; // update
    }
    Value get(const int x, const int l, const int r, const int L, const int R)
    {
        /*
         * get 'sum' from [L,R)
         * starting from [l,r)*/
        if (L <= l && r <= R) // same as set
            return value[x];
        int m = (l + r) / 2;
        push_down(x);
        if (R <= m){
            /*
             * ----------------
             * L  R        
             * l    m   r*/
            // remember, this is return!
            // it means only left part make sense
            return get(ls(x), l, m, L, R);
        }
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
            /*
             * current node id is x,
             * current numbers are in [l,r)*/
            if (l + 1 == r)
            {
                value[x] = init[l];
                return;
            }
            int m = (l + r) / 2;
            // recurse in sons
            self(self, this->ls(x), l, m);
            self(self, this->rs(x), m, r);
            value[x] = value[this->ls(x)] + value[this->rs(x)];
        };
        build(build, 0, 0, n); // start build
    }
};

template <typename Value>
class SegmentTree
{
    /*
     * same as Lazy, but with no lazy
     * it only supports changing in one node*/
    // needs value: operator=, operator+
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
    SegmentTree(const int n, std::vector<Value> init)
        : n(n), value(n * 4)
    {
        assert(init.size() == n);
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
};
