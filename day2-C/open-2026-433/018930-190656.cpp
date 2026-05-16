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

struct Node {
    long long val = 0;
    long long tag = 0;
};

std::vector<long long> arr;
std::vector<Node> tree;

void build(long long v, long long l, long long r) {
    if (r - l == 1) {
        tree[v].val = arr[l];
        return;
    }
    long long m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v].val = std::max(tree[2 * v + 1].val, tree[2 * v + 2].val);
}

void push(long long v, long long l, long long r) {
    long long tag = tree[v].tag;
    tree[v].tag = 0;
    tree[2 * v + 1].tag = std::max(tree[2 * v + 1].tag, tag);
    tree[2 * v + 1].val = std::max(tree[2 * v + 1].val, tag);
    tree[2 * v + 2].tag = std::max(tree[2 * v + 2].tag, tag);
    tree[2 * v + 2].val = std::max(tree[2 * v + 2].val, tag);
}

void update(long long v, long long l, long long r, long long ql, long long qr, long long val) {
    if (ql >= r || l >= qr) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v].val = std::max(tree[v].val, val);
        tree[v].tag = std::max(tree[v].tag, val);
        return;
    }
    push(v, l, r);
    long long m = (l + r) / 2;
    update(2 * v + 1, l, m, ql, qr, val);
    update(2 * v + 2, m, r, ql, qr, val);
    tree[v].val = std::max(tree[2 * v + 1].val, tree[2 * v + 2].val);
}

long long get(long long v, long long l, long long r, long long ql, long long qr) {
    if (ql >= r || l >= qr) {
        return -2e9;
    }
    if (ql <= l && r <= qr) {
        return tree[v].val;
    }
    push(v, l, r);
    long long m = (l + r) / 2;
    return std::max(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    long long n, q;
    std::cin >> n >> q;
    std::vector<std::pair<long long, long long>> seg(n);
    std::vector<long long> line(2 * n);
    long long ii = 0;
    for (long long i = 0; i < n; ++i) {
        long long l, r;
        std::cin >> l >> r;
        seg[i] = {l, r};
        line[ii] = l;
        ++ii;
        line[ii] = r;
        ++ii;
    }
    std::sort(line.begin(), line.end());
    std::sort(seg.begin(), seg.end());
    std::vector<long long> que(q);
    for (long long& elem : que) {
        std::cin >> elem;
    }

    long long ind = 0;
    long long ost = n;
    long long st = 0;
    std::multiset<long long> fin;
    std::vector<long long> ans(n, 1e9);
    tree.assign(4 * q, Node());
    arr.assign(q, 0);
    for (long long pos : line) {
        while (ind < n && seg[ind].first == pos) {
            fin.insert(seg[ind].second);
            ++ind;
            --ost;
        }
        while (!fin.empty()) {
            long long r = *fin.begin();
            if (r < pos) {
                ++st;
                fin.erase(fin.begin());
            } else {
                break;
            }
        }
        //std::cerr << std::min(st * 2, 2 * ost) << '\n';
        if (std::min(st * 2, 2 * ost) >= 0) update(0, 0, q, 0, std::min(std::min(st * 2, 2 * ost), q), (long long)fin.size());
        while (!fin.empty()) {
            long long r = *fin.begin();
            if (r == pos) {
                ++st;
                fin.erase(fin.begin());
            } else {
                break;
            }
        }
        //std::cerr << std::min(st * 2, 2 * ost) << '\n';
        //std::cerr << q << '\n';
        if (std::min(st * 2, 2 * ost) >= 0) update(0, 0, q, 0, std::min(std::min(st * 2, 2 * ost), q), (long long)fin.size());
    }
    for (long long qq : que) {
        //std::cout << (std::max(0, qq - ans[qq - 1]) + 1) / 2 << ' ';
        std::cout << (std::max(0ll, qq - get(0, 0, q, qq - 1, qq)) + 1ll) / 2ll << ' ';
    }
    std::cout << '\n';
    return 0;
}