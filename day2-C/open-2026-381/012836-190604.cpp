#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define all(x) x.begin(), x.end()
using ll = long long;
using ui = unsigned int;
using ull = unsigned long long;
using ld = long double;
template<typename T> 
using orset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll mod = 998244353;

int main () {
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << "Yes";
}
