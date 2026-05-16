#include<bits/stdc++.h>

using namespace std;
//#define int long long
#define all(x) x.begin(),x.end()
struct node {
    int l , r , id;
};

bool cmp(node a , node b) {
    return (a.l == b.l ? a.r > b.r : a.l < b.l);
}

bool cmp1(node a , node b) {
    return (a.r == b.r ? a.l < b.l : a.r < b.r);
}

bool cmp2(node a , node b) {
    return (a.l == b.l ? a.r > b.r : a.l > b.l);
}

int recalc(vector<node> &a) {
    vector<node> c;
    int n = a.size(), bal = 0;
//    sort(c.begin(), c.end() , cmp);
    for (int i = 0 ; i < n ; i++) {
        c.push_back({a[i].l , 1, 0});
        c.push_back({a[i].r , -1, 0});
    }
    int mx = 0;
    sort(c.begin(), c.end() , cmp);
    for(int i = 0 ; i < c.size() ; i++) {
        bal += c[i].r;
        mx = max(mx , bal);
    }
//    cout << '\n';
    return mx;
}
int L , R;
int recalc1(vector<node> &a) {
    vector<node> c;
    int n = a.size(), bal = 0;
    for (int i = 0 ; i < n ; i++) {
        c.push_back({a[i].l , 1 , 0});
        c.push_back({a[i].r , -1, 0});
    }
    int mx = 0;
    sort(c.begin(), c.end() , cmp);
    for(int i = 0 ; i <c.size() ; i++) {
        bal += c[i].r;
        if(i == n - 1) {
            L = c[i].l;
            R = c[i + 1].l;
        }
        mx = max(mx , bal);
    }
    return mx;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n , q;
    cin >> n >> q;
    vector<int> ans(n + 1 , 2e9);
    vector<node> a(n);
    for(int i = 0 ; i < n ; i++) {
        cin >> a[i].l >> a[i].r;
    }
    sort(a.begin(), a.end() , cmp);
    for(int i = 0 ; i < n ; i++) {
        a[i].id = i;
    }
    recalc1(a);
    int z = recalc(a);
    ans[z] = 0;
    vector<node> left , right;
    for(int i = 0 ; i < n ; i++) {
        if(a[i].r <= L) {
            left.push_back(a[i]);
        }
        if(a[i].l >= R) {
            right.push_back(a[i]);
        }
    }
    sort(all(left) , cmp1);
    sort(all(right) , cmp2);
    for(int i = 0 ; i < min((int)left.size() , (int)right.size()); i++) {
        swap(a[left[i].id].r , a[right[i].id].l);
        int z = recalc(a);
        ans[z] = min(ans[z] , i + 1);
    }
    for(int i = n - 2 ; i >= 0 ; i--) {
        ans[i] = min(ans[i] , ans[i + 1]);
    }
    for(int i = 0 ; i< q ; i++) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
 }
