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
void solve() {
	ll n, q; cin >> n >> q;
	vector<pair<ll, ll>>Ot;
	ll ansend = 1e18, anscnt = -1, ansk = -1;
	vector<vector<ll>>ev;
	for (int i = 0; i < n; i++) {
		ll L, R; cin >> L >> R;
		ev.push_back({ L, -1 });
		ev.push_back({ R, 1 });
	}
	sort(ev.begin(), ev.end());
	ll cntR = 0, cntL = n, ind = 0, cnt = 0;
	while (ind < ev.size()) {
		ll j = ind;
		while (j < ev.size() && ev[j][0] == ev[ind][0] && ev[j][1] == -1) {
			cnt++; j++; cntL--;
		}
		
		ll k = min(cntL, cntR);
		ll End = n - cnt - k;
		if (ansend > End) {
			ansend = End;
			anscnt = cnt;
			ansk = k;
		}
		
		while (j < ev.size() && ev[j][0] == ev[ind][0] && ev[j][1] == 1) {
			cnt--; cntR++; j++;
		}
		ind = j;
	}

	vector<ll>ans(n + 1, 1e18);
	for (int i = 0; i <= anscnt; i++)
		ans[i] = 0;
	for (int i = 1; i <= ansk; ++i) {
		ans[anscnt + i * 2 - 1] = i;
		ans[anscnt + i * 2] = i;
	}
	for (int j = anscnt + 2 * ansk + 1; j <= n; j++)
		ans[j] = ans[j - 1] + 1;

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