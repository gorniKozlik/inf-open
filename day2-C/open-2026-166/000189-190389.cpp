#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    int l[n],r[n];
    vector<pair<int,int>> es;
    for(int i = 0;i < n;++i)
    {
        cin >> l[i] >> r[i];
        es.push_back({l[i],-1});
        es.push_back({r[i],1});
    }
    int kz = 0;
    int sum = 0;
    vector<pair<pair<int,int>,int>> ev2;
    sort(es.begin(),es.end());
    for(int i = 0;i < es.size();++i)
    {
        if(es[i].second == -1)
        {
            sum ++;
        }
        else
        {
            sum --;
            kz ++;
        }
       // cout << sum << ' ' << kz << endl;
        ev2.push_back({{sum, -1},0});
        ev2.push_back({{min(sum + kz * 2, sum + (n - sum - kz) * 2), 1},sum});
    }
    for(int i = 0;i < q;++i)
    {
        int k;
        cin >> k;
        ev2.push_back({{k,0},i});
    }
    sort(ev2.begin(),ev2.end());
    multiset<int> opl;
    int ans[q];
  //  cout << "!" << endl;
    for(int i = 0;i < ev2.size();++i)
    {
        //cout << ev2[i].first.first << ' ' << ev2[i].first.second << ' ' << ev2[i].second << endl;
        if(ev2[i].first.second == -1)
        {
            opl.insert(ev2[i].first.first);
        }
        else if(ev2[i].first.second == 1)
        {
            opl.erase(opl.find(ev2[i].second));
        }
        else
        {
           // cout << ev2[i].first.first << ' ' << opl.size() << endl;
            auto it = opl.end();
            it--;
            ans[ev2[i].second] = (ev2[i].first.first - (*it) + 1) / 2; 
        }
    }
    for(int i = 0;i < q;++i)
    {
        cout << ans[i] << ' ';
    }
    cout << "\n";
    return 0;
}
