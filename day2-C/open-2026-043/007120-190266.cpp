#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct Sgt_push {
    long long add;
    Sgt_push() : add(0) {}
    Sgt_push(long long a) : add(a) {}
    Sgt_push apply(Sgt_push other) {
        return add + other.add;
    }
};

struct Sgt_Node {
    long long sm, sz;
    Sgt_Node() : sm(0), sz(0) {}
    Sgt_Node(long long a, long long b) : sm(a), sz(b) {}
    Sgt_Node merge(Sgt_Node other) {
        return Sgt_Node(other.sm + sm, sz + other.sz);
    }
    Sgt_Node apply(Sgt_push other) {
        return Sgt_Node(other.add * sz + sm, sz);
    }
};


struct Seg_tree {
    vector<Sgt_Node> tree;
    vector<Sgt_push> push;
    vector<long long> a;
    long long n;
    void build_q(vector<long long> a2) {
        a = a2;
        n = a.size();
        tree.resize(4 * n);
        push.resize(4 * n);
        build(0, 0, n);
    }

    void build(long long v, long long l, long long r) {
        if (l == r - 1) {
            tree[v] = Sgt_Node(a[l], 1);
            return;
        }
        build(2 * v + 1, l, (l + r) / 2);
        build(2 * v + 2, (l + r) / 2, r);
        tree[v] = tree[2 * v + 1].merge(tree[2 * v + 2]);
    }

    void update(long long v, long long l, long long r, long long ql, long long qr, Sgt_push add) {
        if (ql <= l && r <= qr) {
            tree[v] = tree[v].apply(add);
            push[v] = push[v].apply(add);
            return;
        }
        if (qr <= l || r <= ql) {
            return;
        }
        tree[2 * v + 1] = tree[2 * v + 1].apply(push[v]);
        tree[2 * v + 2] = tree[2 * v + 2].apply(push[v]);
        push[2 * v + 1] = push[2 * v + 1].apply(push[v]);
        push[2 * v + 2] = push[2 * v + 2].apply(push[v]);
        push[v] = Sgt_push();
        update(2 * v + 1, l, (l + r) / 2, ql, qr, add);
        update(2 * v + 2, (l + r) / 2, r, ql, qr, add);
        tree[v] = tree[2 * v + 1].merge(tree[2 * v + 2]);
    }

    void update_q(long long l, long long r, Sgt_push add) {
        update(0, 0, n, l, r, add);
    }

    Sgt_Node get(long long v, long long l, long long r, long long ql, long long qr) {
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        if (qr <= l || r <= ql) {
            return Sgt_Node();
        }
        tree[2 * v + 1] = tree[2 * v + 1].apply(push[v]);
        tree[2 * v + 2] = tree[2 * v + 2].apply(push[v]);
        push[2 * v + 1] = push[2 * v + 1].apply(push[v]);
        push[2 * v + 2] = push[2 * v + 2].apply(push[v]);
        push[v] = Sgt_push();
        return get(2 * v + 1, l, (l + r) / 2, ql, qr).merge(get(2 * v + 2, (l + r) / 2, r, ql, qr));
    }

    Sgt_Node get_q(long long l, long long r) {
        return get(0, 0, n, l, r);
    }
};


struct Node_Aho {
    int go[26];
    int suf, supersuf, par, sz;
    bool term;
    char in;
    Node_Aho() {
        for (int i = 0; i < 26; i++) {
            go[i] = -1;
        }
        suf = -1;
        par = -1;
        sz = 0;
        term = false;
        supersuf = -1;
        in = '#';
    }
};

struct Aho {
    vector<Node_Aho> trie = {Node_Aho()};
    void add(string s) {
        int v = 0;
        for (auto &i : s) {
            if (trie[v].go[i - 'a'] == -1) {
                trie[v].go[i - 'a'] = trie.size();
                trie.push_back(Node_Aho());
                trie.back().par = v;
                trie.back().sz = trie[v].sz + 1;
                trie.back().in = i;
            }
            v = trie[v].go[i - 'a'];
        }
        trie[v].term = true;
    }


    void init(int v) {
        if (trie[v].suf != -1) {
            return;
        }
        //counting suf link
        if (v == 0) {
            trie[v].suf = -2;
        } else if (trie[v].par == 0) {
            trie[v].suf = 0;
        } else {
            trie[v].suf = trie[trie[trie[v].par].suf].go[trie[v].in - 'a'];
        }
        //counting supersuf link
        if (v != 0) {
            if (trie[trie[v].suf].term) {
                trie[v].supersuf = trie[v].suf;
            } else {
                trie[v].supersuf = trie[trie[v].suf].supersuf;
            }
        }
        //counting go
        for (long long i = 0; i < 26; i++) {
            if (trie[v].go[i] == -1) {
                if (v == 0) {
                    trie[v].go[i] = 0;
                } else {
                    trie[v].go[i] = trie[trie[v].suf].go[i];
                }
            }
        }
    }

    void initialize() {
        deque<long long> all;
        all.push_back(0);
        while (!all.empty()) {
            auto v = all[0];
            all.pop_front();
            for (auto &i : trie[v].go) {
                if (i != -1) {
                    all.push_back(i);
                }
            }
            init(v);
        }
    }
};


struct line {
    long long k, b;
    line() : k(0), b(-1e18) {}
    line(long long a, long long c) : k(a), b(c) {}
    long long get(long long x) {
        return k * x + b;
    }
};

struct Node_Li {
    line a;
    Node_Li* l;
    Node_Li* r;
    Node_Li() : a(line()), l(nullptr), r(nullptr) {}
};

const long long C = 1e9;

struct Li_Chao {
    Node_Li* root = new Node_Li();
    void add(Node_Li* v, long long l, long long r, line x) {
        long long mid = (l + r) / 2;
        if (x.get(mid) > v->a.get(mid)) {
            swap(x, v->a);
        }
        if (r == l + 1) {
            return;
        }
        if (x.get(l) > v->a.get(l)) {
            if (v->l == nullptr) {
                v->l = new Node_Li();
            }
            add(v->l, l, mid, x);
        }
        if (x.get(r) > v->a.get(r)) {
            if (v->r == nullptr) {
                v->r = new Node_Li();
            }
            add(v->r, mid, r, x);
        }
    }

    long long get(Node_Li* v, long long l, long long r, long long x) {
        if (v == nullptr) {
            return -1e18;
        }
        if (l == r - 1) {
            return v->a.get(x);
        }
        long long mid = (l + r) / 2;
        if (x < mid) {
            return max(v->a.get(x), get(v->l, l, mid, x));
        }
        return max(v->a.get(x), get(v->r, mid, r, x));
    }
};

bool is_good(vector<long long> a, string s) {
    for (long long i = 1; i < a.size(); i++) {
        if (a[i] != a[i - 1] || s[i] != s[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    #ifdef MAX
    freopen("input.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, q;
    cin >> n >> q;
    vector<pair<long long, long long>> a(n);
    vector<long long> all;
    for (auto &i : a) {
        cin >> i.first >> i.second;
        all.push_back(i.first);
        all.push_back(i.second);
    }
    sort(all.begin(), all.end());
    vector<long long> answers(n + 1, 1e18);
    long long pref = 0;
    ordered_set left, right;
    for (auto &[l, r] : a) {
        left.insert(l);
        right.insert(r);
    }
    for (auto &j : all) {
        long long cnt_l = 0, cnt_r = 0;
        cnt_l = right.order_of_key(j);
        cnt_r = left.size() - left.order_of_key(j);
        long long alr = n - cnt_l - cnt_r;
        // for (auto &[l, r] : a) {
        //     if (r < j) {
        //         cnt_l++;
        //     } else if (j < l) {
        //         cnt_r++;
        //     } else {
        //         alr++;
        //     }
        // }
        pref = max(pref, alr);
        for (long long i = alr; i <= 2 * min(cnt_l, cnt_r) + alr; i++) {
            answers[i] = min(answers[i], (i - alr + 1) / 2);
        }
        if (cnt_l != cnt_r) {
            answers[2 * min(cnt_l, cnt_r) + alr + 1] = min(answers[2 * min(cnt_l, cnt_r) + alr + 1], min(cnt_l, cnt_r) + 1);
        }
    }
    for (long long i = 0; i <= pref; i++) {
        answers[i] =  0;
    }
    while (q--) {
        long long k;
        cin >> k;
        cout << answers[k] << endl;
    }
    /*
    //Sample of ordered set
    ordered_set X;
    X.insert(10);
    X.insert(101);
    cout << *X.find_by_order(10) << endl;
    cout << X.order_of_key(11) << endl;
    */
    //seg_tree is working
    //Hmmm...... HLD or centroids or Aho or grader? I choose grader
    //Hmmm...... HLD or centroids or Aho or stresstests? I choose stresstests
    ///Hmmm...... HLD or centroids or Aho or idk? I choose Aho
    //The time is up. Today we rise. It was true...
    //1 day later...
    //The time is not up yet. I can check everything
}