#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <deque>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <unordered_set>
#include <string>
using namespace std;
struct nit{
    int l, r;
    nit(int l=0, int r=0): l(l), r(r) {}
};
#define left 2*v+1
#define right 2*v+2
int n;
vector<int> t;
vector<int> d;
void change(int v, int l, int r, int x, int y){
    if(l>=y || r<=x){
        return;
    }
    if(l>=x && r<=y){
        t[v]++;
    } else {
        int m=(l+r)/2;
        int val=t[v]-max(t[left], t[right]);
        t[left]+=val;
        t[right]+=val;
        change(left, l, m, x, y);
        change(right, m, r, x, y);
        t[v]=max(t[left], t[right]);
    }
}
void change(int x, int y){
    change(0, 0, d.size(), x, y+1);
}
int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, q;
    cin>>n>>q;
    vector<nit> a(n);
    vector<int> ans(n+1, 52);
    for(int i=0; i<n; i++){
        cin>>a[i].l>>a[i].r;
        d.push_back(a[i].l);
        d.push_back(a[i].r);
    }
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end())-d.begin());
    t.resize(4*d.size());
    for(int i=0; i<n; i++){
        int l=lower_bound(d.begin(), d.end(), a[i].l)-d.begin();
        int r=lower_bound(d.begin(), d.end(), a[i].r)-d.begin();
        change(l, r);
    }
    set<pair<int, int>> l_g, r_g;
    for(int i=0; i<n; i++){
        l_g.insert({-a[i].l, i});
        r_g.insert({a[i].r, i});
    }
    int x;
    int cnt=0;
    for(x=0; x<=t[0]; x++){
        ans[x]=cnt;
    }
    while(l_g.size()>0){
        if(x>n){
            break;
        }
        auto [l, i]=*l_g.begin();
        l=-l;
        l_g.erase(l_g.begin());
        auto [r, j]=*r_g.begin();
        r_g.erase(r_g.begin());
        if(i==j || r>=l){
            continue;
        }
        //cout<<i<<" "<<j<<"\n"<<r<<" "<<l<<" "<<t[0]<<"\n\n";
        l=lower_bound(d.begin(), d.end(), l)-d.begin();
        r=lower_bound(d.begin(), d.end(), r)-d.begin();
        change(r, l);
        change(r, l);
        cnt++;
        for(; x<=t[0]; x++){
            ans[x]=cnt;
        }
    }
    while(q--){
        int k;
        cin>>k;
        cout<<ans[k]<<" ";
    }
    return 0;
}