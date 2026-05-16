#include <iostream>
#include<vector>
#include<algorithm>
#include<set>
#pragma GCC target("avx")
using namespace std;
int check(set<pair<int,int>> b){
    int ans=0;
    int cur=0;
    //cout<<"B"<<endl;
    for (auto x: b){
        if (x.second==-1){
            cur++;
        }
        //cout<<x.first<<" "<<cur<<endl;
        ans=max(ans,cur);
        if (x.second==1){
            cur--;
        }
    }
    return ans;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<pair<int,int>> a(n);
    set<pair<int,int>> b;
    set<pair<int,int>> c;
    for (int i=0;i<n;i++){
        cin>>a[i].first>>a[i].second;
        b.insert({a[i].first,-1});
        b.insert({a[i].second,1});
        c.insert(a[i]);
    }
    vector<int> ans(n+1);
    for (int k=0;k<n+1;k++){
        while (check(b)<k){
            //cout<<"A"<<endl;
            //cout<<check(b)<<" "<<k<<endl;
            auto s1=*c.begin();
            auto s3=c.end();
            s3--;
            auto s2=*s3;
            //cout<<s1.first<<" "<<s1.second<<endl;
            //cout<<s2.first<<" "<<s2.second<<endl;
            int l1,r1,l2,r2;
            l1=s1.first;
            l2=s2.first;
            r1=s1.second;
            r2=s2.second;
            //cout<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<endl;
            b.erase({l1,-1});
            b.erase({r1,1});
            b.erase({l2,-1});
            b.erase({r2,1});
            b.insert({min(l1,l2),-1});
            b.insert({max(r1,r2),1});
            b.insert({min(r1,l2),-1});
            b.insert({max(r1,l2),1});
            c.erase({min(l1,l2),max(r1,r2)});
            c.erase({min(r1,l2),max(r1,l2)});
            ans[k]++;
            //for (auto t:b){
                //cout<<t.first<<" "<<t.second<<endl;
            //}
        }
        b.clear();
        c.clear();
        for (int i=0;i<n;i++){
            b.insert({a[i].first,-1});
            b.insert({a[i].second,1});
            c.insert(a[i]);
        }
    }
    for (int i=0;i<q;i++){
        int y;
        cin>>y;
        cout<<ans[y]<<" ";
    }
    cout<<endl;
}



