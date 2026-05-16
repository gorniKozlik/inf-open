#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define its(a) a.begin(), a.end()
#define print(a) {for (auto i : a) {cout << i << " ";} cout << "\n";}
#define printPairs(a) for (auto t : a) {cout << t.first << " " << t.second << "\n";}
#define scan(a) {for (int i = 0; i < a.size(); ++i) cin >> a[i];}
constexpr ll INFLL = 1e18 + 130;
constexpr int INFINT = 1e9 + 13;
constexpr int MAXN = 1e6;
constexpr int LOGN = 18;
constexpr int M = 998'244'353;
std::mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());
template <typename type, typename cmp = less<type>>
using pbds_set = tree<type, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

int binPow(int a, int n) {
	if (!n) return 1;
	if (n & 1) return 1ll * a * binPow(a, n - 1) % M;
	return binPow(1ll * a * a % M, n / 2);
}

struct Fenwick {
	int n;
	vector <int> tree;

	void init(int n) {
		this->n = n;
		tree.assign(n + 1, 0);
	}

	void update(int i, int x) {
		for (++i; i <= n; i += (i & (-i))) {
			tree[i] += x;
		}
	}

	int get_pref(int i) {
		int res = 0;
		for (++i; i > 0; i -= (i & (-i))) {
			res += tree[i];
		}
		return res;
	}

	int get(int l, int r) {
		return get_pref(r) - get_pref(l - 1);
	}
};

void solve() {
	ll n, m, k, x; cin >> n >> m >> k >> x;
	vector <ll> h(n), r(n);
	ll mxH = -1;
	for (int i = 0; i < n; ++i) {
		cin >> h[i] >> r[i];
		mxH = max(h[i], mxH);
	}
	vector <pair <ll, ll>> sc(m);
	for (int i = 0; i < m; ++i) {
		cin >> sc[i].first >> sc[i].second;
	}
	sort(its(sc));
	ll need = INFLL;
	vector <ll> sufMin(m + 1, INFLL);
	for (int i = m - 1; i >= 0; --i) {
		sufMin[i] = min(sufMin[i + 1], sc[i].second);
	}
	vector <ll> prefMaxH(n + 1, 0), prefSumR(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		prefMaxH[i + 1] = max(prefMaxH[i + 1], h[i]);
		prefSumR[i + 1] = prefSumR[i] + r[i];
	}
	vector <int> ind(m, 0);
	vector <pair <int, int>> pr(n);
	vector <ll> dp(n + 1, -INFLL);
	dp[0] = x;
	for (int i = 1; i <= n; ++i) {
		ll curMxh = 0;
		for (int j = i - 1; j >= i - min(k, 300) && j >= 0; j--) {
			curMxh = max(curMxh, h[j]);
			int L = -1, R = m;
			while (R - L > 1) {
				int mid = (L + R) >> 1;
				if (sc[mid].first >= curMxh) {
					R = mid;
				}
				else {
					L = mid;
				}
			}
			if (R == m) {
				break;
			}
			if (dp[j] >= sufMin[R]) dp[i] = max(dp[i], dp[j] - sufMin[R] + (prefSumR[i] - prefSumR[j]));
		}
	}
	if (dp[n] >= 0) cout << "Yes";
	else cout << "No";
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	solve();
}

/*
*/
