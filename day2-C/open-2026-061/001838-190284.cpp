#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <string>
#include <vector>

using namespace std;
using ll=long long;
const ll inf = 1e18;



struct segtree {
	ll lb, rb;
	ll mn = inf;
	ll add = inf;
	segtree* l = 0, *r = 0;
	segtree(ll lb, ll rb) :lb(lb), rb(rb) {
		if (lb < rb) {
			ll m = lb + (rb - lb) / 2;
			l = new segtree(lb, m);
			r = new segtree(m + 1, rb);
		}
	}
	void push() {
		if (add != inf) {
			mn = min(mn, add);
			if (lb < rb) {
				l->add = min(l->add, add);
				r->add = min(r->add, add);
			}
			add = inf;
		}
	}
	ll get(ll lq, ll rq) {
		if (min(rb, rq) < max(lb, lq)) {
			return inf;
		}
		push();
		if (lb >= lq && rb <= rq) {
			return mn;
		}
		return min(l->get(lq, rq), r->get(lq, rq));
	}
	void upd(ll lq, ll rq, ll val) {
		if (min(rb, rq) < max(lb, lq)) {
			return;
		}
		push();
		if (lb >= lq && rb <= rq) {
			mn = min(mn, val);
			if (lb < rb) {
				l->add = min(l -> add, val);
				r->add = min(r->add, val);
			}
			return;
		}
		l->upd(lq, rq, val);
		r->upd(lq, rq, val);
		mn = min(l->mn, r->mn);
	}
};


ll l[200001];
ll r[200001];
ll ans[200001];
int main() {
#ifdef _DEBUG
	freopen("in.txt", "r", stdin);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, q;
	cin >> n >> q;
	vector<pair<ll, ll>> v;
	for (int i = 1; i <= n; ++i) {
		cin >> l[i] >> r[i];
		v.push_back({ l[i],-1 });
		v.push_back({ r[i],1 });
		ans[i] = inf;
	}
	sort(v.begin(), v.end());
	ll koll = 0;
	ll kolp = 0;
	segtree s0(1, n);
	segtree s1(1, n);
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].second == -1) {
			++kolp;
		}
		if (v[i].second == 1) {
			ll s = min(koll, n - koll - kolp);
			if (kolp % 2== 0) {
				ll t = -(kolp) / 2;
				s0.upd(1, kolp + 2 * s, t);
			}
			else {
				ll t = -(kolp) / 2;
				s1.upd(1, kolp + 2 * s, t);
			}

		}
		else {
			ll s = min(koll, n - koll - kolp);
			if (kolp % 2 == 0) {
				ll t = -(kolp) / 2;
				s0.upd(1, kolp + 2 * s, t);
			}
			else {
				ll t = -(kolp) / 2;
				s1.upd(1, kolp + 2 * s, t);
			}
			if (koll > s) {
				ans[kolp + 2 * s + 1] = min(ans[kolp + 2 * s + 1], s + 1);
			}
		}

		if (v[i].second == 1) {
			++koll;
			--kolp;
		}
	}
	for (int i = 1; i <= n; ++i) {
		ll k1 = (i + 1) / 2;
		ans[i] = min(ans[i], s0.get(i, i) + k1);
		ll k2 = i / 2;
		ans[i] = min(ans[i], s1.get(i, i) + k2);
	}
	for (int i = 1; i <= q; ++i) {
		ll k;
		cin >> k;
		cout << ans[k] << " ";
	}
	cout << "\n";
}