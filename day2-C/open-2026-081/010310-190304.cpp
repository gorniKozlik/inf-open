#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cmath>
#include <random>
#include <unordered_map>
#include <deque>
typedef long long ll;
typedef long double ld;
using namespace std;
ll get(ll n, ll cnt, ll k, ll ind) {
	if (ind <= cnt)
		return 0;
	ind -= cnt;
	if (ind <= 2 * k)
		return (ind+1) / 2;
	ind -= 2 * k;
	return ind + k;
}
void solve() {
	ll n, q; cin >> n >> q;
	vector<pair<ll, ll>>Ot;
	ll anscnt = -1, ansk = -1;
	vector<vector<ll>>ev;
	for (int i = 0; i < n; i++) {
		ll L, R; cin >> L >> R;
		ev.push_back({ L, -1 });
		ev.push_back({ R, 1 });
	}
	sort(ev.begin(), ev.end());
	ll cntR = 0, cntL = n, ind = 0, cnt = 0;
	vector<pair<ll, ll>>answer;
	while (ind < ev.size()) {
		ll j = ind;
		while (j < ev.size() && ev[j][0] == ev[ind][0] && ev[j][1] == -1) {
			cnt++; j++; cntL--;
		}

		ll k = min(cntL, cntR);
		answer.push_back({ cnt, k });

		while (j < ev.size() && ev[j][0] == ev[ind][0] && ev[j][1] == 1) {
			cnt--; cntR++; j++;
		}
		ind = j;
	}
	sort(answer.rbegin(), answer.rend());
	vector<ll>ans(n + 1, 1e18);
	for (int i = 0; i < answer.size(); i++) {
		ll cnt = answer[i].first, k = answer[i].second;
		ll l = -1, r = n+1;
		while (r - l > 1) {
			ll mid = (l + r) / 2;
			if (ans[mid] > get(n, cnt, k, mid))
				r = mid;
			else
				l = mid;
		}
		for (int j = r; j <= n; j++)
			ans[j] = get(n, cnt, k, j);
	}
	while (q--) {
		ll k; cin >> k;
		cout << ans[k] << " ";
	}
}
int main()
{
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	ll _T = 1;//cin>>_T;
	while (_T--)
		solve();
}