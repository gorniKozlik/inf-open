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
	int n, q; cin >> n >> q;
	vector <pair <int, int>> seg(n);
	for (int i = 0; i < n; ++i) {
		cin >> seg[i].second >> seg[i].first;
	}
	for (int i = 0; i < q; ++i) {
        ll k; cin >> k;
        cout << k - 1 << " ";
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	solve();
}

/*
*/
