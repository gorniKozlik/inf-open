#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
//#pragma GCC target("avx2,bmi2")
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
using ul = unsigned long long;
using ld = long double;
using lll = __int128;
constexpr ll mod = 998244353;

ll add(ll a, ll b) {
    return (a + b) % mod;
}
ll mult(ll a, ll b) {
    return (a * b) % mod;
}
ll sub(ll a, ll b) {
    return add(a, mod - b) % mod;
}
ll powm(ll a, ll p) {
    ll K = 1;
    while (p) {
        if (p & 1) K = mult(K, a);
        a = mult(a, a);
        p >>= 1;
    }
    return K;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

}
