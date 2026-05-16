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
    std::multiset<int> fin;
    for (int qi = 0; qi < q; ++qi) {
        int ans = 1e9;
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
                ans = std::min(ans, (q + 1) / 2);
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
                ans = std::min(ans, (q + 1) / 2);
            }
        }
        std::cout << ans << ' ';
    }
    std::cout << '\n';
    return 0;
}