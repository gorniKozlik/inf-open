#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
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

int L , R;
void recalc1(vector<node> &a) {
    vector<node> c;
    int n = a.size(), bal = 0;
    for (int i = 0 ; i < n ; i++) {
        c.push_back({a[i].l , 1 , 0});
        c.push_back({a[i].r , -1, 0});
    }
    int mx = 0;
    sort(c.begin(), c.end() , cmp);
    L = c[n - 1].l;
    R = c[n].l;
}

struct susy {
    int val , add;
};

struct sg {
    vector<susy> tree;
    void push(int num , int vl , int vr) {
        tree[num].val += tree[num].add;
        if (vl + 1 != vr) {
            tree[num * 2 + 1].add += tree[num].add;
            tree[num * 2 + 2].add += tree[num].add;
        }
        tree[num].add = 0;
    }
    int get(int num, int vl , int vr , int l , int r) {
        push(num , vl , vr);
        if (l <= vl && vr <= r) {
            return tree[num].val;
        }
        if (r <= vl || vr <= l) {
            return 0;
        }
        int vm = (vl + vr) / 2;
        return max(get(num * 2 + 1 , vl , vm , l , r) , get(num * 2 + 2 , vm , vr , l , r));
    }
    void update(int num , int vl , int vr, int l , int r , int x) {
        push(num , vl , vr);
//        cout << 1 << endl;
        if (l <= vl && vr <= r) {
            tree[num].add += x;
            push(num , vl , vr);
            return;
        }
        if (r <= vl || vr <= l) {
            return;
        }
        int vm = (vl + vr) / 2;
        update(num * 2 + 1 , vl , vm , l , r , x);
        update(num * 2 + 2 , vm , vr , l , r , x);
        tree[num].val = max(tree[num * 2 + 1].val , tree[num * 2 + 2].val);
    }
};
cc_hash_table<int , int> id;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n , q;
    cin >> n >> q;
    vector<int> ans(n + 5 , 2e9);
    vector<node> a(n);
    set<int> st;
    for(int i = 0 ; i < n ; i++) {
        cin >> a[i].l >> a[i].r;
        st.insert(a[i].l);
        st.insert(a[i].r);
        st.insert(a[i].l + 1);
        st.insert(a[i].l - 1);
        st.insert(a[i].r + 1);
        st.insert(a[i].r - 1);
    }
    int cnt = 0;
    for(auto i : st) {
        id[i] = cnt++;
    }
    sort(a.begin(), a.end() , cmp);
    for(int i = 0 ; i < n ; i++) {
        a[i].id = i;
    }
    vector<node> left , right;
    sg tr;
    recalc1(a);
    tr.tree.resize(4 * cnt , {0 , 0});
    for(int i = 0 ; i < n ; i++) {
        tr.update(0 , 0 , cnt , id[a[i].l] , id[a[i].r] + 1 , 1);
        if(a[i].r <= L) {
            left.push_back(a[i]);
        }
        if(a[i].l >= R) {
            right.push_back(a[i]);
        }
    }
    int z = tr.get(0 , 0 , cnt , 0 , cnt);
    ans[z] = 0;
    sort(all(left) , cmp1);
    sort(all(right) , cmp2);
    for(int i = 0 ; i < min((int)left.size() , (int)right.size()); i++) {
        tr.update(0 , 0 , cnt , id[a[left[i].id].l] , id[a[left[i].id].r] + 1 , -1);
        tr.update(0 , 0 , cnt , id[a[right[i].id].l] , id[a[right[i].id].r] + 1 , -1);
        swap(a[left[i].id].r , a[right[i].id].l);
        tr.update(0 , 0 , cnt , id[a[right[i].id].l] , id[a[right[i].id].r] + 1 , 1);
        tr.update(0 , 0 , cnt , id[a[right[i].id].l] , id[a[right[i].id].r] + 1 , 1);
        int z = tr.get(0 , 0 , cnt , 0 , cnt);
        ans[z] = min(ans[z] , i + 1);
    }
    for(int i = n - 1 ; i >= 0 ; i--) {
        ans[i] = min(ans[i] , ans[i + 1]);
    }
    for(int i = 0 ; i< q ; i++) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
 }
