#include <algorithm>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define F first
#define S second
#define Vector2 pair <int, int>
#define print(a) for (const auto& x : a) cout << x << ' ';

const int INF = 1e9;

void solve()
{
	int n, q;
	cin >> n >> q;
	vector <Vector2> segs(n);
	vector <int> vs;
	for (auto& [x, y] : segs) {
		cin >> x >> y;
		vs.push_back(x);
		vs.push_back(y);
	}
	sort(all(vs));
	vs.erase(unique(all(vs)), vs.end());
	auto get = [vs] (int x) -> int {
		return lower_bound(all(vs), x) - vs.begin();
	};
	int m = sz(vs);
	vector <int> cntl(m, 0), cntr(m, 0), diffp(m + 1, 0), diff(m + 1, 0);
	for (int i = 0; i < n; ++i) {
		cntl[get(segs[i].F)]++;
		cntr[get(segs[i].S)]++;
		diffp[get(segs[i].F)]++;
		diff[get(segs[i].F)]++;
		diff[get(segs[i].S)]--;
		diffp[get(segs[i].S) + 1]--;
	}
	vector <int> prefmx(m, 0), curmx(max(0, m - 1));
	for (int i = 0; i < m; ++i) {
		prefmx[i] = prefmx[max(0, i - 1)] + diffp[i];
	}
	for (int i = 0; i < m - 1; ++i) {
		curmx[i] = curmx[max(0, i - 1)] + diff[i];
	}
	vector <int> prefl(m, 0), prefr(m, 0);
	for (int i = 0; i < m; ++i) {
		prefl[i] = prefl[max(0, i - 1)] + cntl[i];
	}
	for (int i = 0; i < m; ++i) {
		prefr[i] = prefr[max(0, i - 1)] + cntr[i];
	}
	vector <int> mx(m + 1, -INF);
	for (int i = 0; i < m; ++i) {
		int l = (i > 0 ? prefr[i - 1] : 0);
		int r = n - prefl[i];
		mx[min(l, r)] = max(mx[min(l, r)], prefmx[i]);
	}
	for (int i = 0; i < m - 1; ++i) {
		int l = prefr[i];
		int r = n - prefl[i];
		mx[min(l, r)] = max(mx[min(l, r)], curmx[i]);
	}
	vector <int> pref(n + 1, -INF), suf(n + 2, -INF);
	for (int i = 1; i <= n; ++i) {
		pref[i] = pref[i - 1];
		if (mx[i - 1] == -INF) {
			continue;
		}
		pref[i] = max(pref[i], mx[i - 1] + 2 * (i - 1));
	}
	for (int i = n; i >= 0; --i) {
		suf[i] = max(suf[i + 1], mx[i]);
	}
	vector <int> nxt(n + 1);
	for (int i = 0; i <= n; ++i) {
		nxt[i] = max(pref[i], (suf[i] == -INF ? -INF : suf[i] + 2 * i));
	}
	vector <int> ans(n + 1, INT_MAX);
	int ptr = 0;
	for (int i = 1; i <= n; ++i) {
		while (ptr <= n && nxt[ptr] < i) {
			++ptr;
		}
		if (ptr <= n) {
			ans[i] = ptr;
		}
	}
	while (q--) {
		int k;
		cin >> k;
		cout << ans[k] << ' ';
	}
}

signed main()
{
	cin.tie(nullptr)->ios_base::sync_with_stdio(false);
	solve();
	return 0;
}