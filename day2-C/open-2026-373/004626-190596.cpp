#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <complex>
#include <stdlib.h>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <cstring>
#include <string.h>
#include <math.h>
#include <cmath>
#include <chrono>
#include <random>
#include <float.h>
#include <cfloat>
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sq(x) (x) * (x)
#define cube(x) (x) * (x) * (x)
using ll = long long;
using db = long double;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const ll LINF = 1LL << 62;
const db EPS = 1e-9;
using namespace std;

ll binpow(ll x, ll n) {
	if (!n) {
		return 1;
	}
	ll bp = binpow(x, n >> 1);
	if (n & 1)
		return (((bp * bp) % MOD) * x) % MOD;
	return (bp * bp) % MOD;
}

struct seg_tree {};
struct DSU {};
struct sparse_table {};
struct fenwick {};

inline void solve() {

	int n, k;
	cin >> n >> k;

	vector <pair<int, int>> vec;
	vector <int> st, end;
	priority_queue <int, vector <int>, greater<int>> right;
	priority_queue <int> left;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		vec.push_back({ a, 1 });
		vec.push_back({ b, -1 });
		st.push_back(a);
		end.push_back(b);
		right.emplace(b);
		left.emplace(a);
	}
	sort(all(vec));
	sort(all(st));
	sort(all(end));

	// pick potential and l r
	int l = -1, r = -1, best = 0;
	int curl = -1, curr = -1;
	int p = 0;
	int x = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (vec[i].second == -1) {
			int pp = min(int(upper_bound(all(end), curl) - end.begin()), int(st.size() - 1 - (lower_bound(all(st), curr) - st.begin())));
			curr = vec[i].first;
			if (x + pp > best + p) {
				best = x;
				l = curl;
				r = curr;
				p = pp;
			}
			x--;
		}
		else {
			curl = vec[i].first;
			x++;
		}
	}
	vector <int> res(k, 0);
	vector <pair<int, int>> quer(k);
	for (int i = 0; i < k; i++) {
		int a; cin >> a;
		quer[i] = { a, i };
	}
	sort(all(quer));

	int c = 0;
	for (int i = 0; i < k; i++) {

		while (best < quer[i].first) {
			int ll = left.top();
			int rr = right.top();
			if (ll < rr || (ll < l || rr > r)) {
				break;
			}
			left.pop(); right.pop();
			
			if (ll > r && rr < l) {
				best += 2;
			}
			else {
				best++;
				r = ll;
				l = rr;
			}
			right.emplace(ll);
			left.emplace(rr);
			c++;
		}
		res[quer[i].second] = c;
	}

	for (int i = 0; i < k; i++) {
		cout << res[i] << " ";
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.setf(ios_base::fixed); cout.precision(8);

	solve();
	return 0;
}