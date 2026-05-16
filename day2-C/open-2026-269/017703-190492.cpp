
#include<iostream>
#include<vector>
#include<algorithm>
#include<array>
#include<set>
using namespace std;
#define int long long
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define ppb pop_back
const int maxn = 500, mod = 998244353, inf = 1e18;

void solve() {
	int n, q;
	cin >> n >> q;
	vector <pair<int, int>> a(n);
	vector <int> t;
	for (auto& x : a) {
		cin >> x.ff >> x.ss;
		t.pb(x.ff);
		t.pb(x.ss);
	}
	sort(all(t));
	t.resize(unique(all(t)) - t.begin());
	int m = 2 * sz(t);
	vector <int> l, r;
	for (auto& x : a) {
		x.ff = 2 * (lower_bound(all(t), x.ff) - t.begin());
		l.pb(x.ff);
		x.ss = 2 * (lower_bound(all(t), x.ss) - t.begin());
		r.pb(x.ss);
	}
	sort(all(l));
	sort(all(r));
	vector <int> cnt(m);
	vector <array <int, 3>> e(2 * n);
	vector <int> ans(q);
	for (int i = 0; i < n; ++i) {
		e[2 * i] = { a[i].ff, 0, i };
		e[2 * i + 1] = { a[i].ss, 1, i };
	}
	sort(all(e));
	int c = 0, mx = 0;
	for (int i = 0; i < 2 * n - 1; ++i) {
		if (e[i][1]) --c;
		else ++c;
		for (int j = e[i][0]; j < e[i + 1][0]; ++j)
			cnt[j] = max(cnt[j], c);
	}
	while (q--) {
		int k;
		cin >> k;
		int mn = inf;
		for (int i = 0; i < m; ++i) {
			int tmp = cnt[i], lt = lower_bound(all(r), i) - r.begin(), rt = l.end() - upper_bound(all(l), i);
			if (min(rt, lt) * 2 >= k - tmp) {
				mn = min(mn, max(0ll, (k - tmp + 1) / 2));
			}
		}
		cout << mn << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	//cin >> t;
	while (t--)
		solve();
}
