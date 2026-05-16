#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <immintrin.h>

int ans[200'000];
int line[400'000];
std::pair<int, int> seg[200'000];
int que[200'000];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    int ii = 0;
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        seg[i] = {l, r};
        line[ii] = l;
        ++ii;
        line[ii] = r;
        ++ii;
    }
    std::sort(line, line + 2 * n);
    std::sort(seg, seg + n);
    for (int i = 0; i < q; ++i) {
        std::cin >> que[i];
    }
    int ind = 0;
    std::multiset<int> fin;
    for (int qi = 0; qi < q; ++qi) {
        ans[qi] = 1e9;
        int ost = n;
        int st = 0;
        ind = 0;
        for (int pos : line) {
            //std::cout << pos << '\n';
            while (ind < n && seg[ind].first == pos) {
                fin.insert(seg[ind].second);
                ++ind;
                --ost;
            }
            //std::cout << seg[ind].l << ' ' << pos << '\n';
            while (!fin.empty()) {
                int r = *fin.begin();
                if (r < pos) {
                    ++st;
                    fin.erase(fin.begin());
                } else {
                    break;
                }
            }
            //std::cout << pos << ' ' << st.size() << ' ' << fin.size() << '\n';
            //std::cout << fin.size() << '\n';
            int q = std::max(0, que[qi] - (int)fin.size());
            //std::cout << qi << ' ' << q << '\n';
            if (st * 2 >= q && 2 * ost >= q) {
                ans[qi] = std::min(ans[qi], (q + 1) / 2);
            }

            while (!fin.empty()) {
                int r = *fin.begin();
                if (r == pos) {
                    ++st;
                    fin.erase(fin.begin());
                } else {
                    break;
                }
            }
            q = std::max(0, que[qi] - (int)fin.size());
            //std::cout << qi << ' ' << q << '\n';
            if (st * 2 >= q && 2 * ost >= q) {
                ans[qi] = std::min(ans[qi], (q + 1) / 2);
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}