#include <iostream>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <random>
#include <numeric>


using namespace std;
using ll = long long;
using ld = long double;
using ui = unsigned int;
using ull = unsigned long long;

struct Seg {
    int l, r;

    bool operator<(const Seg a) const {
        return l < a.l;
    }
};

struct Event {
    int t, type, id;

    bool operator<(const Event a) const {
        if (t != a.t) return t < a.t;
        if (type != a.type) return type < a.type;
        return id < a.id;
    }
};

istream& operator>>(istream& is, Seg &a) {
    is >> a.l >> a.r;
    return is;
}

int count(vector<Event> evs) {
    int cur = 0;
    int ans = 0;
    for (auto [t, type, id] : evs) {
        if (type == 0) {
            cur++;
        } else {
            cur--;
        }
        ans = max(ans, cur);
    }
    return ans;
}

const int INF = 2e9;

struct SegTree {
    struct Node {
        int mx = 0;
        int add = 0;
        Node *left, *right;

        Node(int v) {
            mx = v;
            add = 0;
            left = right = nullptr;
        }
    };
    
    Node* root = nullptr;
    int n;

    SegTree(int n) : n(n) {
        root = new Node(0);
    }

    void push(Node *v) {
        if (v->left) {
            v->left->add += v->add;
            v->left->mx += v->add;
        }
        if (v->right) {
            v->right->add += v->add;
            v->right->mx += v->add;
        }
        v->add = 0;
    }

    void children(Node *v) {
        push(v);
        if (!v->left) {
            v->left = new Node(v->mx);
        }
        if (!v->right) {
            v->right = new Node(v->mx);
        }
    }

    void update(Node *v) {
        children(v);
        v->mx = max(v->left->mx, v->right->mx);
    }

    

    void add_seg(Node *v, int l, int r, int ql, int qr, int val) {
        if (ql >= r || l >= qr) {
            return;
        }
        if (ql <= l && qr >= r) {
            v->mx += val;
            v->add += val;
            return;
        }
        children(v);
        int m = (r + l) / 2;
        add_seg(v->left, l, m, ql, qr, val);
        add_seg(v->right, m, r, ql, qr, val);
        update(v);
    }

    int get(Node* v, int l, int r, int ql, int qr) {
        if (ql >= r || l >= qr) {
            return 0;
        }
        if (ql <= l && qr >= r) {
            return v->mx;
        }
        children(v);
        int m = (r + l) / 2;
        return max(get(v->left, l, m, ql, qr), get(v->right, m, r, ql, qr));
    }

    int get() {
        return get(root, 0, n, 0, n);
    }

    void add_seg(int l, int r, int val) {
        add_seg(root, 0, n, l, r, val);
    }
};

bool check(int l1, int r1, int l2, int r2) {
    bool f1 = l1 == min(l1, l2);
    bool f2 = r1 == max(r1, r2);
    bool f3 = l2 == min(l1, l2);
    bool f4 = r2 = max(r1, r2);
    return (!f1 || !f2) && (!f3 || !f4);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    set<Seg> segs;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        segs.emplace(l, r);
    }
    SegTree cur(1e9 + 1);
    for (auto [l, r] : segs) {
        cur.add_seg(l, r + 1, 1);
    }
    int cnt = cur.get();
    vector<int> dp(n + 1, 1e9);
    dp[0] = 0;
    for (int k = 1; k <= n; ++k) {
        dp[k] = dp[k - 1];
        if (k <= cnt) continue;
        bool f = false;
        while (!f && segs.size() > 1) {
            auto [l1, r1] = *segs.begin();
            auto [l2, r2] = *segs.rbegin();
            if (check(l1, r1, l2, r2)) {
                cur.add_seg(min(l1, l2), max(r1, r2) + 1, 1);
                cur.add_seg(min(max(l1, l2), min(r1, r2)), max(max(l1, l2), min(r1, r2)) + 1, 1);
                cur.add_seg(l1, r1 + 1, -1);
                cur.add_seg(l2, r2 + 1, -1);
                if (cur.get() > cnt) {
                    f = true;
                }
            }
            segs.erase({l1, r1});
            segs.erase({l2, r2});
        }
        cnt = cur.get();
        dp[k]++;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << dp[k] << ' ';
    }
}