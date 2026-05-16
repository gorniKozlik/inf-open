#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll

#pragma gcc optimize("O3")
#pragma gcc target("avx3,avx2")

using pii = pair<int, int>;

template<int mod>
struct modint{
    int val;
    modint(int x){
        if(x >= mod){
            x %= mod;
        }
        val = x;
    }
    modint(){
        val = 0;
    }
};

template<int mod>
modint<mod> operator+(modint<mod> a, modint<mod> b){
    return a.val + b.val - (a.val + b.val >= mod ? mod : 0);
}

template<int mod>
modint<mod> operator-(modint<mod> a, modint<mod> b){
    return a.val - b.val + (a.val - b.val < 0 ? mod : 0);
}

template<int mod>
modint<mod> operator*(modint<mod> a, modint<mod> b){
    return ((ll)a.val * b.val) % mod;
}

template<int mod>
modint<mod> bpow(modint<mod> a, int x){
    if(x == 0){
        return 1;
    }
    modint<mod> res = bpow(a, x / 2);
    res = res * res;
    if(x % 2 == 1){
        res = res * a;
    }
    return res;
}

template<int mod>
modint<mod> inv(modint<mod> a){
    return bpow(a, mod - 2);
}

template<int mod>
modint<mod> operator/(modint<mod> a, modint<mod> b){
    return a * inv(b);
}

template<int mod>
istream& operator>>(istream &in, modint<mod> &num){
    int val;
    auto ret = (in >> val);
    if(val >= mod){
        val %= mod;
    }
    num.val = val;
    return ret;
}

template<int mod>
ostream& operator<<(ostream &out, const modint<mod> &num){
    return out << num.val;
}

void solve(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cout << i << ' ';
    }   
    cout << '\n';
}

signed main(){
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}