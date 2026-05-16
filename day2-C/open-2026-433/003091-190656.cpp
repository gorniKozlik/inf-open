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

struct Event {
    int val;
    int type;
    int id;
};

bool comp(Event a, Event b) {
    if (a.val != b.val) return a.val < b.val;
    return a.val > b.val;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<Event> line;
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        line.push_back({l, 1, i});
        line.push_back({r, -1, i});
    }
    std::sort(line.begin(), line.end(), comp);
    int cnt = 0;
    std::set<int> setik;
    for (Event ev : line) {
        ++cnt;
        setik.insert(ev.id);
        if (cnt == n) {
            break;
        }
    }
    std::cout << n - setik.size() << '\n';
    return 0;
}