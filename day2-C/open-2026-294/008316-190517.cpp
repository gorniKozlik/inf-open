#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

//#define __lg log2

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll MOD = 1e9 + 7;
const int N = 5e5 + 5;
const int LOG = 21;
const ll INF = 1e16;

int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);

	int n, q;
	cin >> n >> q;

	vector<int> tt;

	vector<pair<int, int>> tmp;

	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;

		tmp.push_back({ l, r });
		tt.push_back(l);
		tt.push_back(r);
	}

	sort(tt.begin(), tt.end());

	map<int, int> has;
	int cnt = 1;
	for (auto i : tt) {
		if (!has[i]) {
			has[i] = cnt++;
		}
	}

	for (auto& i : tmp) {
		i.first = has[i.first];
		i.second = has[i.second];
	}

	vector<int> cntt(2 * n + 1);
	vector<int> cnt_left(2 * n + 1);
	vector<int> cnt_right(2 * n + 1);
	for (int i = 1; i <= 2 * n; i++) {
		for (auto j : tmp) {
			if (j.first < i && j.second > i) {
				cntt[i]++;
			}

			if (j.second <= i) {
				cnt_left[i]++;
			}

			if (j.first >= i) {
				cnt_right[i]++;
			}
		}
	}

	int mx = 0;
	for (int i = 1; i <= 2 * n; i++) {
		mx = max(mx, cntt[i]);
	}

	vector<int> req;

	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;

		if (k <= mx) {
			cout << 0 << ' ';
		}
		else {
			int ans = 1e9;
			for (int i = 1; i <= 2 * n; i++) {
				int lf = cnt_left[i];
				int rf = cnt_right[i];

				if (cntt[i] + 2ll * min(lf, rf) >= k) {
					ans = min(ans, (k - cntt[i] + 1) / 2);
				}
			}

			cout << ans << ' ';
		}
	}
}

