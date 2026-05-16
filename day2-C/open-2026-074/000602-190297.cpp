#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

#define ll long long
#define vc vector
#define db double
#define str string
#define its(a) (a).begin(), (a).end()
#define itsr(a) (a).rbegin(), (a).rend()
#define sz(a) (a).size()
#define tstr to_string
#define scan(a) for (auto &_i:a) cin >> _i;

const ll MOD = 998244353;
const ll INF = 1e18 + 18;
void solve() {
	/*vc<ll> tr;
	auto get = [&](auto get, int v, int l, int r, int lq, int rq) -> ll {
		if (lq <= l and r <= rq) return tr[v];
		if (rq <= l or r <= lq) return 0;
		int mid = (r + l) >> 1;
		return get(get, 2 * v + 1, l, mid, lq, rq) + get(get, 2 * v + 2, mid, r, lq, rq);
	};
	auto build = [&](auto build, int v, int l, int r) -> void {
		if (r - l == 1) {
			tr[v] = a[l];
			return;
		}
		int mid = (r + l) >> 1;
		build(build, 2 * v + 1, l, mid);
		build(build, 2 * v + 2, mid, r);
		tr[v] = tr[2 * v + 1] + tr[2 * v + 2];
	};
	auto st = [&](auto st, int v, int l, int r, int e, int x) -> void {
		if (r - l == 1) {
			tr[v] = x;
			return;
		}
		int mid = (r + l) >> 1;
		if (e < mid) st(st, 2 * v + 1, l, mid, e, x);
		else st(st, 2 * v + 2, mid, r, e, x);
		tr[v] = tr[2 * v + 1] + tr[2 * v + 2];
	};
	auto dfs = [&](auto dfs, ll u) -> void {
		trs[u] = 1;
		
		for (auto v : g[u]) {
			dfs(dfs, v);
			trs[u] += trs[v];
		}
	};
	*/

	ll n, q; cin >> n >> q;
	vc<pair<ll, ll>> segs(n);
	for (auto& [i, j] : segs) cin >> i >> j;
	vc<ll> qs(q); scan(qs);


	vc<tuple<ll, ll, ll>> ev;
	for (int i = 0; i < n; ++i) ev.push_back({ segs[i].first, 0, i }), ev.push_back({ segs[i].second, 1, i });
	sort(its(ev));

	ll cnt = 0;
	pair<ll, ll> mx = { -1, -1 };

	
	for (auto [x, t, o] : ev) {
		if (t == 1) {
			cnt--;
			//++cntl;
		}
		else {
			++cnt;
			//--cntr;
			mx = max(mx, { cnt, o });
		}
	}
	
	vc<ll> ans(n+1, INF);
	ll cntl = 0, cntr = n;
	cnt = 0;
	for (auto [x, t, o] : ev) {
		if (t == 1) {
			++cntl;
			--cnt;
		}
		else {
			--cntr;
			++cnt;
			if (t == 0) {
				ans[cnt] = 0;
				ll cur = 0;
				for (int i = cnt + 1; i <= n; ++i) {
					if (cntl and cntr) {
						--cntl, --cntr;
						ans[i] = min(ans[i], cur + 1);
						ans[i + 1] = min(ans[i],cur + 1);
						i++;
						cur++;
					}
					else {
						ans[i] = min(ans[i], cur + 1);
						cur++;
					}
				}
			}
		}

	}

	//ll mx = ans[n];
	for (int i = n-1; i >= 1; --i) ans[i] = min(ans[i], ans[i + 1]);
	for (auto i : qs) cout << ans[i] << '\n';
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	ll _t = 1;
	//cin >> _t;
	while (_t--)
		solve();
}
