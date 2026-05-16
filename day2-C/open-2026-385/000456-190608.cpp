// cf: stupid_moron
#include <bits/stdc++.h>
#pragma GCC target("avx")
using namespace std;
using ll = long long;
using ld = long double;
const int inf = 1e9 + 2145;
mt19937 rng(time(0));

const int N = 4e5 + 21;
int n, q;
int l[N], r[N], k[N];
int diff[N], cur[N];
int st[20][N], lg[N];

int get(int l, int r) {
	if (l > r) return 0;
	int k = lg[r - l + 1];
	return max(st[k][l], st[k][r - (1 << k) + 1]);
}

void solve() {
	cin >> n >> q;

	vector<int> a;
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
		a.push_back(l[i]);
		a.push_back(r[i]);
	}

	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());

	for (int i = 0; i < n; i++) {
		l[i] = lower_bound(a.begin(), a.end(), l[i]) - a.begin();
		r[i] = lower_bound(a.begin(), a.end(), r[i]) - a.begin();
	}

	fill(diff, diff + 2 * n + 1, 0);
	for (int i = 0; i < n; i++) {
		diff[l[i]]++; diff[r[i]]--;
	}

	int x = 0;
	for (int i = 0; i < 2 * n; i++) {
		x += diff[i];
		cur[i] = x;
	}

	for (int i = 0; i < 2 * n; i++)
		st[0][i] = cur[i];
	for (int i = 2; i <= 2 * n; i++)
		lg[i] = lg[i / 2] + 1;
	for (int j = 1; (1 << j) <= 2 * n; j++)
	for (int i = 0; i + (1 << j) <= 2 * n; i++)
		st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);

	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;

		int l, r;
		tie(l, r) = make_pair(k - 1, 2 * n - k - 1);
		int ans = 0;
		int qs = get(l, r);
		if (qs < k) ans = (k - qs + 1) / 2;
		cout << ans << ' ';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t = 1;
	// cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}