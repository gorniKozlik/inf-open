#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;
#define ll long long
#define al(a) a.begin(), a.end()
#define con continue

ll inf = 1e8;

struct ST {
	vector<ll> a;
	vector<ll> t;
	void build(int v, int l, int r) {
		if (l + 1 == r) {
			t[v] = a[l];
			return;
		}
		ll m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
		t[v] = max(t[v * 2], t[v * 2 + 1]);
	}
	ll get(int v, int vl, int vr, int ql, int qr) {
		if (vl >= ql && vr <= qr) {
			return t[v];
		}
		if (vl >= qr || vr <= ql) {
			return -inf;
		}
		ll m = (vl + vr) / 2;
		return max(get(v * 2, vl, m, ql, qr), get(v * 2 + 1, m, vr, ql, qr));
	}
};

int main() {
	int n, q;
	cin >> n >> q;
	vector<pair<ll, ll>> nit(n);
	vector<ll> crd;
	for (int i = 0; i < n; i++) {
		ll l, r;
		cin >> l >> r;
		nit[i].first = l;
		nit[i].second = r;
		crd.push_back(l);
		crd.push_back(r);
	}
	sort(al(crd));
	unordered_map<ll, int> mapa;
	for (int i = 1; i <= size(crd); i++) {
		mapa[crd[i-1]] = i;
	}
	for (int i = 0; i < n; i++) {
		nit[i].first = mapa[nit[i].first];
		nit[i].second = mapa[nit[i].second];
	}
	vector<ll> raz(n * 2 + 5, 0);
	for (auto p : nit) {
		raz[p.first]++;
		raz[p.second]--;
	}
	vector<ll> cnt(n*2+5);
	ll curc = 0;
	for (int i = 1; i <= n * 2 + 4; i++) {
		curc += raz[i];
		cnt[i] = curc;
	}
	vector<ll> t((n * 2 + 5) * 4);
	ST st;
	st.a = cnt;
	st.t = t;
	st.build(1, 0, (n * 2 + 5));
	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;
		ll l = k;
		ll r = 2 * n - k+1;
		ll mx = st.get(1, 0, (n * 2 + 5), l, r);
		ll tmp = k - mx;
		ll ans = (tmp > 0 ? (tmp + 1) / 2 : 0);
		cout << ans << ' ';
	}
	cout << endl;
}