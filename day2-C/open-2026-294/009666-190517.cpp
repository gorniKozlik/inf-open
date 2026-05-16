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

	vector<int> another(2 * n + 1);

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

		another[i.first] = i.second;
		another[i.second] = i.first;
	}

	vector<int> cntt(2 * n + 1);
	vector<int> cnt_left(2 * n + 1);
	vector<int> cnt_right(2 * n + 5);

	for (auto i : tmp) {
		cntt[i.first + 1]++;
		cntt[i.second]--;
		cnt_left[i.second]++;
		cnt_right[i.first]++;
	}

	for (int i = 1; i <= 2 * n; i++) {
		cntt[i] += cntt[i - 1];
		cnt_left[i] += cnt_left[i - 1];
	}

	for (int i = 2 * n; i >= 1; i--) {
		cnt_right[i] += cnt_right[i + 1];
	}

	int mx = 0;
	for (int i = 1; i <= 2 * n; i++) {
		mx = max(mx, cntt[i]);
	}

	vector<ll> mxx(2 * n + 5, 0);
	// 				ans = min(ans, (k - cntt[i]) / 2);

	for (int i = 1; i <= 2 * n; i++) {
		int lf = cnt_left[i];
		int rf = cnt_right[i];

		if (another[i] > i) {
			mxx[min(2ll * n, cntt[i] + 2ll * min(lf, rf - 1) + 1)] = max(mxx[min(2ll * n, cntt[i] + 2ll * min(lf, rf - 1) + 1)], (ll)cntt[i]);
		}
		else {
			mxx[min(2ll * n, cntt[i] + 2ll * min(lf - 1, rf) + 1)] = max(mxx[min(2ll * n, cntt[i] + 2ll * min(lf - 1, rf) + 1)], (ll)cntt[i]);
		}

		mxx[min(2ll * n, cntt[i] + 2ll * min(lf, rf))] = max(mxx[min(2ll * n, cntt[i] + 2ll * min(lf, rf))], (ll)(cntt[i] - 1));
	}

	for (int i = 2 * n; i >= 1; i--) {
		mxx[i] = max(mxx[i + 1], mxx[i]);
	}

	vector<int> req;

	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;

		if (k <= mx + 1) {
			cout << 0 << ' ';
			continue;
		}
		else {
			cout << (k - mxx[k]) / 2 << ' ';
		}
	}
}

