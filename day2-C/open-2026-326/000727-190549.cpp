#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <bitset>
#include <cmath>
#include <cstring> 
#include <iostream>
#include <string>
#pragma ivdep
#pragma GCC target("avx2")
#define fi first
#define se second
typedef long long ll;
using namespace std;
typedef pair<ll, ll> pi;
//namespace __gnu_pbds{
//  typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//}
//using namespace __gnu_pbds;

const ll maxN = 1e6 + 1, maxA = 1e6, mod = 998244353;

struct Event {int x, t, idx;};
struct Query {int l, r, idx;};
inline bool operator<(Event a, Event b){
	if (a.x != b.x) return a.x < b.x;
	return a.t > b.t;
}

inline bool operator>(Event a, Event b){
	return b < a;
}

vector <Query> qs;
set <Event> ev;
int check() {
	int ans = 0, cnt = 0;
	for (Event e : ev) {
		if (e.t) {
			cnt++;
		}
		ans = max(ans, cnt);
		if (!e.t) cnt--;
	}
	return ans;
}
void solve() {
	int n, q; cin >> n >> q;
	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r;
		qs.push_back({l, r, i});
		ev.insert({l, 1, i});
		ev.insert({r, 0, i});
	}

	sort(qs.begin(), qs.end(), [&](Query a, Query b) {
		if (a.l != b.l) return a.l < b.l;
		return a.r < b.r;
	});

	vector <int> ans(n);
	int max0 = check();
	for (int i = 0; i < max0; i++) ans[i] = 0;
	int j = 0;
	for (int i = max0; i < n;) {
		ev.erase({qs[j].r, 0, qs[j].idx});
		ev.erase({qs[n - j - 1].l, 1, qs[n - j - 1].idx});
		ev.insert({qs[j].r, 1, qs[j].idx});
		ev.insert({qs[n - j - 1].l, 0, qs[n - j - 1].idx});
		j++;
		int maxv = check();
		for (int k = i; k < maxv; k++) {
			ans[k] = j;
		}
		i = maxv;
	}

	while (q--) {
		int x; cin >> x; x--;
		cout << ans[x] << ' ';
	}

}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll T = 1;
	while (T--) {
		solve();
	}
}