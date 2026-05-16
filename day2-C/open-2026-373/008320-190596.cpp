// C

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
	vector <int> res(k, INF);
	vector <int> ans(3001, INF);

	for (int i = 0; i < k; i++) {
		int q; cin >> q;
		if (ans[q] == INF) {

			int l = -1, r = -1;
			int best = 0;
			for (int j = 0; j < 2 * n; j++) {
				vector <pair<int, int>> vec_ = vec;
				vector <int> st_ = st, end_ = end;
				priority_queue <int, vector <int>, greater<int>> right_ = right;
				priority_queue <int> left_ = left;
				if (vec_[j].second == -1) {
					r = vec_[j].first;

					int best_ = best;
					int c = 0;
					while (best_ < q) {
						int ll = left_.top();
						int rr = right_.top();
						if (ll < rr || ll < l || rr > r || (rr == l && ll == r)) {
							break;
						}
						left_.pop(); right_.pop();

						if (ll > r && rr < l) {
							best_ += 2;
						}
						else {
							best_++;
							if (rr == r) {
								l = r;
								r = right_.top();
							}
							else if (ll == l) {
								r = l;
								l = left_.top();
							}
						}
						right_.emplace(ll);
						left_.emplace(rr);
						c++;
					}
					if (best_ >= q) {
						res[i] = min(res[i], c);
						ans[q] = min(ans[q], c);
					}

					best--;
				}
				else {
					l = vec[j].first;
					best++;
				}
			}
		}
		else {
			res[i] = ans[q];
		}
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