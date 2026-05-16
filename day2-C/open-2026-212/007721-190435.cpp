/*#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pair<int, int>>;

int main()
{
    int n, q;
    cin >> n >> q;

    vi l(n), r(n), all;
    for (int i = 0; i < n; ++i)
    {
        cin >> l[i] >> r[i];
        all.push_back(l[i]);
        all.push_back(r[i]);
    }

    sort(all.begin(), all.end());
    unordered_map<int, int> fromBigToLitte;
    for (int i = 0; i < all.size(); ++i)
        fromBigToLitte[all[i]] = i;

    for (int i = 0; i < n; ++i)
    {
        l[i] = fromBigToLitte[l[i]];
        r[i] = fromBigToLitte[r[i]];
    }
    
    vi st(2 * n);

    for (int i = 0; i < n; ++i)
    {
        for (int j = l[i]; j < r[i]; ++j)
            st[j]++;
    }

    while (q-- > 0)
    {
        int k;
        cin >> k;

        int tmp = 0;
        for (int i = k - 1; i < 2 * n - k; ++i)
            tmp = max(tmp, st[i]);

        //int tmp = st.get(k - 1, 2 * n - k);
        cout << max((k - tmp + 1) / 2, 0) << ' ';
    }
}
*/




#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pair<int, int>>;

class ST
{
private:
    int n;
    vi tree, lazy;

    void push(int v, int l, int r)
    {
        tree[v] += lazy[v];
        if (l + 1 != r)
        {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v];
        }
        lazy[v] = 0;
    }

    void add(int v, int l, int r, int ql, int qr, int x)
    {
        push(v, l, r);
        if (ql == l && r == qr)
        {
            lazy[v] = x;
            return;
        }

        int m = (l + r) / 2;
        if (qr <= m)
            add(2 * v, l, m, ql, qr, x);
        else if (ql >= m)
            add(2 * v + 1, m, r, ql, qr, x);
        else
        {
            add(2 * v, l, m, ql, m, x);
            add(2 * v + 1, m, r, m, qr, x);
        }

        push(2 * v, l, m);
        push(2 * v + 1, m, r);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }

    int get(int v, int l, int r, int ql, int qr)
    {
        push(v, l, r);
        if (ql == l && r == qr)
            return tree[v];

        int m = (l + r) / 2;
        if (qr <= m)
            return get(2 * v, l, m, ql, qr);
        if (ql >= m)
            return get(2 * v + 1, m, r, ql, qr);
        return max(get(2 * v, l, m, ql, m), get(2 * v + 1, m, r, m, qr));
    }

public:
    ST (int n) : n(n)
    {
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }

    void add(int ql, int qr)
    {
        add(1, 0, n, ql, qr, 1);
    }

    int get(int ql, int qr)
    {
        return get(1, 0, n, ql, qr);
    }
};

int main()
{
    int n, q;
    cin >> n >> q;

    vi l(n), r(n), all;
    for (int i = 0; i < n; ++i)
    {
        cin >> l[i] >> r[i];
        all.push_back(l[i]);
        all.push_back(r[i]);
    }

    sort(all.begin(), all.end());
    unordered_map<int, int> fromBigToLitte;
    for (int i = 0; i < all.size(); ++i)
        fromBigToLitte[all[i]] = i;

    for (int i = 0; i < n; ++i)
    {
        l[i] = fromBigToLitte[l[i]];
        r[i] = fromBigToLitte[r[i]];
    }
    
    ST st(2 * n);

    for (int i = 0; i < n; ++i)
        st.add(l[i], r[i]);

    while (q-- > 0)
    {
        int k;
        cin >> k;

        int tmp = st.get(k - 1, 2 * n - k);
        cout << max(0, (k - tmp + 1) / 2) << ' ';
    }
}