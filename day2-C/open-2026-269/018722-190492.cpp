
#include<iostream>
#include<vector>
#include<algorithm>
#include<array>
#include<set>
using namespace std;
//#define int long long
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define ppb pop_back
const int maxn = 5e5, mod = 998244353, inf = 1e9;

pair<int, int> a[maxn];
int cnt[2 * maxn];
pair<int, int> e[2 * maxn];

void solve() {
	int n, q;
	cin >> n >> q;
	vector <int> t;
	for (int i = 0; i < n; ++i) {
		cin >> a[i].ff >> a[i].ss;
		t.pb(a[i].ff);
		t.pb(a[i].ss);
	}
	sort(all(t));
	t.resize(unique(all(t)) - t.begin());
	int m = 2 * sz(t);
	vector <int> l, r;
	for (int i = 0; i < n; ++i) {
		a[i].ff = 2 * (lower_bound(all(t), a[i].ff) - t.begin());
		l.pb(a[i].ff);
		a[i].ss = 2 * (lower_bound(all(t), a[i].ss) - t.begin());
		r.pb(a[i].ss);
	}
	sort(all(l));
	sort(all(r));
	for (int i = 0; i < n; ++i) {
		e[2 * i] = { a[i].ff, 0 };
		e[2 * i + 1] = { a[i].ss, 1 };
	}
	sort(e, e + 2 * n);
	int c = 0, mx = 0;
	for (int i = 0; i < 2 * n - 1; ++i) {
		if (e[i].ss) --c;
		else ++c;
		for (int j = e[i].ff; j < e[i + 1].ff; ++j)
			cnt[j] = max(cnt[j], c);
	}
	while (q--) {
		int k;
		cin >> k;
		int mn = inf;
		for (int i = 0; i < m; ++i) {
			int tmp = cnt[i], lt = lower_bound(all(r), i) - r.begin(), rt = l.end() - upper_bound(all(l), i);
			if (min(rt, lt) * 2 >= k - tmp) {
				mn = min(mn, max(0, (k - tmp + 1) / 2));
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
