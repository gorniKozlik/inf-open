#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<deque>
#include<iomanip>
#include<queue>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<bitset>
#include<cmath>
#include<algorithm>
#include<random>
#include<ctime>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,bmi,popcnt")

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using uint = unsigned int;

mt19937 mt(time(0));
const int N = 2e5 + 2, mod = 998244353, inf = 1e9 + 100;
const ll llinf = 1e18 + 1000;
int n, q, al[N], ar[N], a[N * 2], ans[N];
vector<int> add[N], del[N];
priority_queue<int> pq1, pq2;
void ins(int x) {
	pq1.push(x);
}
void ers(int x) {
	pq2.push(x);
}
int get(int x) {
	while (!pq2.empty() && pq1.top() == pq2.top()) {
		pq1.pop();
		pq2.pop();
	}
	return (x + 1 - pq1.top()) / 2;
}

void solve() {
	cin >> n >> q;
	vector<int> sz;
	for (int i = 0; i < n; ++i) {
		cin >> al[i] >> ar[i];
		sz.push_back(al[i]);
		sz.push_back(ar[i]);
	}
	sort(all(sz));
	for (int i = 0; i < n; ++i) {
		++a[lower_bound(all(sz), al[i]) - sz.begin()];
		--a[lower_bound(all(sz), ar[i]) - sz.begin()];
	}
	for (int i = 1; i < n * 2; ++i) a[i] += a[i - 1];
	for (int i = 0; i + 1 < n * 2; ++i) {
		int cnt = a[i];
		int mx = min(i + 1, n * 2 - i - 1);
		add[cnt].push_back(cnt);
		del[mx + 1].push_back(cnt);
	}
	for (int i = 0; i <= n; ++i) {
		for (auto j : add[i]) ins(j);
		for (auto j : del[i]) ers(j);
		ans[i] = pq1.empty() ? 0 : get(i);
	}
	while (q--) {
		int x;
		cin >> x;
		cout << ans[x] << '\n';
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt = 1;
	//cin >> tt;
	while (tt--) {
		solve();
		cout << '\n';
		cout.flush();
	}
	return 0;
}