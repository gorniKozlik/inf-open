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

struct Seg {
    int l;
    int r;
    int id;
};

bool comp(Seg a, Seg b) {
    if (a.l != b.l) {
        return a.l < b.l;
    }
    if (a.r != b.r) {
        return a.r < b.r;
    }
    return a.id < b.id;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<Seg> seg(n);
    std::vector<int> line(2 * n);
    int ii = 0;
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        seg[i] = {l, r, i};
        line[ii] = l;
        ++ii;
        line[ii] = r;
        ++ii;
    }
    std::sort(line.begin(), line.end());
    std::sort(seg.begin(), seg.end(), comp);
    std::vector<int> que(q);
    for (int& elem : que) {
        std::cin >> elem;
    }
    int ind = 0;
    std::vector<int> ans(q, 1e9);
    for (int qi = 0; qi < q; ++qi) {
        std::set<std::pair<int, int>> fin;
        int ost = n;
        int st = 0;
        ind = 0;
        for (int pos : line) {
            //std::cout << pos << '\n';
            while (ind < n && seg[ind].l == pos) {
                fin.insert({seg[ind].r, seg[ind].id});
                ++ind;
                --ost;
            }
            //std::cout << seg[ind].l << ' ' << pos << '\n';
            while (!fin.empty()) {
                int r = fin.begin()->first;
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
                int r = fin.begin()->first;
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
    for (int elem : ans) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
    return 0;
}