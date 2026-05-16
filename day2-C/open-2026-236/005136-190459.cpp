//#define NDEBUG
//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using ll = long long;

using std::vector;
using std::make_pair;
using std::pair;

template<typename T>
void print(std::vector<T> a) {
    for (const T& i : a) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> l[i] >> r[i];
    }
    std::vector<int> k(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> k[i];
    }
    std::set<int> rs;
    std::set<int> ls;
    for (int i = 0; i < n; ++i) {
        ls.insert(l[i]);
        rs.insert(r[i]);
    }
    int cnt = 0;
    while (*ls.rbegin() > *rs.begin()) {
        int x = *rs.begin();
        rs.erase(rs.begin());
        int y = *ls.rbegin();
        ls.erase(--ls.end());
        rs.insert(y);
        ls.insert(x);
        ++cnt;
    }
    std::cout << cnt << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
}

