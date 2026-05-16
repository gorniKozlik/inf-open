#include <bits/stdc++.h>
#define ll long long
#define int ll
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(), x.rend()
#define uniq(x) x.erase(unique(all(x)), x.end())
#define fast_cin() cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0)

#pragma optimize("O3")
#pragma target("avx2")
using namespace std;

mt19937 rng(696969);

struct pa {
    int x;
    bool nac;
};

struct pp {
    int da,cnt,idx;
};

struct segtree {
    vector<int> t;
    int n;
    segtree(vector<pp> &a) {
        if (!a.empty()) {
            n = a.size();
            t.resize(4*n);
            build(0, 0, n, a);
        }
    }
    void build(int p, int l, int r, vector<pp> &a) {
        if (r-l == 1) {
            t[p] = a[l].da;
            return;
        }
        int m = (l+r)/2;
        build(2*p+1, l, m, a);
        build(2*p+2, m, r, a);
        t[p] = min(t[2*p+1], t[2*p+2]);
    }

    int get(int p, int l, int r, int lx, int rx) {
        if (rx <= lx) return 2e18;
        if (l >= rx || lx >= r) return 2e18;
        if (l >= lx && rx >= r) return t[p];
        int m = (l+r)/2;
        return min(get(2*p+1, l, m, lx, rx), get(2*p+2, m, r, lx, rx));
    }
};

signed main() {
    fast_cin();
    int n,q; cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<pa> po;
    for (auto &i: a) {
        cin >> i.first >> i.second;
        po.push_back({i.first, true});
        po.push_back({i.second, false});
    }
    vector<int> k(q);
    for (int &i: k) cin >> i;

    sort(all(po), [](pa a, pa b) {
        return a.x < b.x;
    });

    vector<int> cnt(2*n);
    int now = 0;
    for (int i = 0; i < 2*n; ++i) {
        if (po[i].nac) ++now;
        cnt[i] = now;
        if (!po[i].nac) --now;
    }
    vector<int> da(2*n);
    vector<pp> b1,b2;
    for (int i = 0; i < 2*n; ++i) {
        int dl = (i-cnt[i]+1)/2,
        dr = n-cnt[i]-dl;
        da[i] = min(dl, dr);
        if (po[i].nac && dl > dr)
            b1.push_back({da[i], cnt[i], i});
        if (!po[i].nac && dr > dl)
            b2.push_back({da[i], cnt[i], i});
    }

    vector<pp> pon(2*n);
    for (int i = 0; i < 2*n; ++i) {
        pon[i].cnt = cnt[i];
        pon[i].da = da[i];
        pon[i].idx = i;
    }
    sort(all(b1), [](pp a, pp b) {
        return a.da*2+a.cnt < b.da*2+b.cnt;
    });
    sort(all(b2), [](pp a, pp b) {
        return a.da*2+a.cnt < b.da*2+b.cnt;
    });
    sort(all(pon), [](pp a, pp b) {
        return a.da*2+a.cnt < b.da*2+b.cnt;
    });

    vector<int> mns(2*n);
    mns[2*n-1] = pon[2*n-1].cnt;
    for (int i = 2*n-2; i >= 0; --i) {
        mns[i] = max(mns[i+1], pon[i].cnt);
    }

    segtree sg1(b1), sg2(b2);

    for (int &j: k) {
        int mn = 2e18;
        int id = lower_bound(all(pon), pp {0, j, 0}, [](pp a, pp b) {
            return a.da*2+a.cnt < b.da*2+b.cnt;
        })-pon.begin();
        if (id < 2*n) mn = max(0LL, (j-mns[id]+1)/2);
        if (!b1.empty()) {
            id = lower_bound(all(b1), pp {0, j-1, 0}, [](pp a, pp b) {
                return a.da*2+a.cnt < b.da*2+b.cnt;
            })-b1.begin();
            if (id < b1.size()) {
                if (b1[id].da*2+b1[id].cnt == j-1) {
                    int id2 = upper_bound(all(b1), pp {0, j-1, 0}, [](pp a, pp b) {
                    return a.da*2+a.cnt < b.da*2+b.cnt;})-b1.begin();
                    mn = min(mn, sg1.get(0, 0, (int)b1.size(), id, id2)+1);
                }
            }   
        }
        if (!b2.empty()) {
            id = lower_bound(all(b2), pp {0, j-1, 0}, [](pp a, pp b) {
                return a.da*2+a.cnt < b.da*2+b.cnt;
            })-b2.begin();
            if (id < b2.size()) {
                if (b2[id].da*2+b2[id].cnt == j-1) {
                    int id2 = upper_bound(all(b2), pp {0, j-1, 0}, [](pp a, pp b) {
                    return a.da*2+a.cnt < b.da*2+b.cnt;})-b2.begin();
                    mn = min(mn, sg2.get(0, 0, (int)b2.size(), id, id2)+1);
                }
            }
        }
        cout << mn << ' ';
    }
}

// мин по всем,
// (j-cnt[i]+1)/2
// кот
// da[i]*2+cnt[i] >= j

// меняется только j.

// сорт по
// da[i]*2+cnt[i]

// мин штуки на суф

// макс cnt на суф

// штуки где po[i].nac && dl > dr
// штуки где !po[i].nac && dr > dl
// если da[i]*2+cnt[i] == j-1
// то мин= da[i]+1;