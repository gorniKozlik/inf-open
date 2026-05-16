#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll

#pragma gcc optimize("O3")
#pragma gcc target("avx3,avx2")

using pii = pair<int, int>;

struct Node{
    int max = 0;
    int psh = 0;
    int left = -1;
    int right = -1;
    Node(){}
    Node(int x){
        max = x;
    }

};

const int NODES = 1e6;
Node t[NODES];
struct SegTree{
    int nodes = 1;

    int left(int v){
        return (t[v].left != -1 ? t[v].left : t[v].left = nodes++);
    }

    int right(int v){
        return (t[v].right != -1 ? t[v].right : t[v].right = nodes++);
    }

    void push(int v){
        if(t[v].psh == 0){
            return;
        }
        t[v].max += t[v].psh;
        t[left(v)].psh += t[v].psh;
        t[right(v)].psh += t[v].psh;
        t[v].psh = 0;
    }

    void update(int v, int l, int r, int ql, int qr, int x){
        push(v);
        if(qr <= l || r <= ql){
            return;
        }
        if(ql <= l && r <= qr){
            t[v].psh += x;
            push(v);
            return;
        }
        int mid = (l + r) / 2;
        update(left(v), l, mid, ql, qr, x);
        update(right(v), mid, r, ql, qr, x);
        t[v].max = max(t[t[v].left].max, t[t[v].right].max);
    }

    int get(int v, int l, int r, int ql, int qr){
        if(v == -1 || qr <= l || r <= ql){
            return 0;
        }
        push(v);
        if(ql <= l && r <= qr){
            return t[v].max;
        }
        int mid = (l + r) / 2;
        return max(get(t[v].left, l, mid, ql, qr), get(t[v].right, mid, r, ql, qr));
    }
};
const int inf = 1e9 + 2;
void solve(){
    int n,  q;
    cin >> n >> q;
    set<pii> seg;
    SegTree st;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        seg.insert({l, r});
        st.update(0, 0, inf, l, r + 1, 1);
    }
    vector<int> ans(n + 1);
    for(int i = 1; i <= n && n > t[0].max; i++){
        bool could = false;
        int er1a, er1b, er2a, er2b, ina, inb;
        for(auto [l1, r1] : seg){
            for(auto [l2, r2] : seg){
                int l = max(l1, l2);
                int r = min(r1, r2);
                if(l <= r){
                    continue;
                }
                swap(l, r);
                int mx = st.get(0, 0, inf, l, r + 1);
                if(mx == t[0].max){
                    could = true;
                    er1a = l1;
                    er1b = r1;
                    er2a = l2;
                    er2b = r2;
                    ina = l;
                    inb = r;
                    ans[mx+1] = i;
                    st.update(0, 0, inf, l, r + 1, 2);
                    break;
                }
            }
            if(could){
                break;
            }
        }
        if(could){
            seg.erase({er1a, er1b});
            seg.erase({er2a, er2b});
            seg.insert({ina, inb});
        } else {
            assert(false);
        }
    }
}

signed main(){
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}