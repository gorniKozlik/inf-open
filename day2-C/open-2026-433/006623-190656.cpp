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

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;
    std::vector<std::pair<int, int>> seg(n);
    std::vector<int> line(2 * n);
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
    std::sort(line.begin(), line.end());
    std::sort(seg.begin(), seg.end());
    std::vector<int> que(q);
    for (int& elem : que) {
        std::cin >> elem;
    }

    int ind = 0;
    int ost = n;
    int st = 0;
    std::multiset<int> fin;
    std::vector<int> ans(n, 1e9);
    for (int pos : line) {
        while (ind < n && seg[ind].first == pos) {
            fin.insert(seg[ind].second);
            ++ind;
            --ost;
        }
        while (!fin.empty()) {
            int r = *fin.begin();
            if (r < pos) {
                ++st;
                fin.erase(fin.begin());
            } else {
                break;
            }
        }
        for (int qi = 1; qi <= n; ++qi) {
            int q = std::max(0, qi - (int)fin.size());
            if (st * 2 >= q && 2 * ost >= q) {
                ans[qi - 1] = std::min(ans[qi - 1], (q + 1) / 2);
            }
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
        for (int qi = 1; qi <= n; ++qi) {
            int q = std::max(0, qi - (int)fin.size());
            if (st * 2 >= q && 2 * ost >= q) {
                ans[qi - 1] = std::min(ans[qi - 1], (q + 1) / 2);
            }
        }
    }
    for (int q : que) {
        std::cout << ans[q - 1] << ' ';
    }
    std::cout << '\n';
    return 0;
}