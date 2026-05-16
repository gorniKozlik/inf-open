#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int, int> > e;
    e.reserve(2 * n);

    for (int i = 0; i < n; i++)
    {
        int l, r;
        std::cin >> l >> r;
        e.push_back(std::make_pair(l, 1));
        e.push_back(std::make_pair(r, -1));
    }

    std::sort(e.begin(), e.end());

    int m = 2 * n - 1;
    std::vector<int> a(m + 1);
    int c = 0;

    for (int i = 1; i <= m; i++)
    {
        c += e[i - 1].second;
        a[i] = c;
    }

    int s = 1;
    while (s < m)
    {
        s <<= 1;
    }

    std::vector<int> t(2 * s);

    for (int i = 1; i <= m; i++)
    {
        t[s + i - 1] = a[i];
    }

    for (int i = s - 1; i >= 1; i--)
    {
        t[i] = std::max(t[i << 1], t[i << 1 | 1]);
    }

    std::vector<int> ans(n + 1);

    for (int k = 1; k <= n; k++)
    {
        int l = k + s - 1;
        int r = 2 * n - k + s - 1;
        int mx = 0;

        while (l <= r)
        {
            if (l & 1)
            {
                mx = std::max(mx, t[l]);
                l++;
            }
            if (!(r & 1))
            {
                mx = std::max(mx, t[r]);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }

        if (mx >= k)
        {
            ans[k] = 0;
        }
        else
        {
            ans[k] = (k - mx + 1) / 2;
        }
    }

    for (int i = 0; i < q; i++)
    {
        int k;
        std::cin >> k;
        if (i)
        {
            std::cout << ' ';
        }
        std::cout << ans[k];
    }

    std::cout << '\n';
    return 0;
}