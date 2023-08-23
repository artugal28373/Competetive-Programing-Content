
/**
https://codeforces.com/problemset/problem/1184/E2
**/
#include <bits/stdc++.h>
using namespace std;
//#include<ext/pb_ds/tree_policy.hpp>
//#include<ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
//template<typename temp>
//using ordered_set = tree<temp, null_type, less_equal<temp>, rb_tree_tag,tree_order_statistics_node_update>;
#define PB push_back
#define PP pop_back
#define Endl "\n"
//#define int long long int
#define MP make_pair
#define MT make_tuple
#define sxof sizeof
#define sx size()
#define lengt size()
#define __lcm(b, c) (b/__gcd(b, c))*c
#define V vector
#define DE deque
#define UE queue
//#define ff first.first
//#define fs first.second
//#define sf second.first
//#define ss second.second
//#define s  second
//#define f  first

using pii =  pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
//const int mod = 998244353;
//const int mod = (1e9)+7;
const int mxn = (1e7)+5;
const int inf = (int)1e17;
////////////////////////
int bigmod(int b, int p, int mod) {
    int res = 1;
    for(; p; p/=2) {
        if(p&1) res  = (res * b)%mod;
        b = (b*b)%mod;
    }
    return res;
}
vector<tuple<int, int, int, int>> edges;
vector<int> p, rnk, dis, t;
void init(int n){
  p.resize(n+1);
  t.resize(n+1);
  dis.resize(n+1, -1);
  rnk.resize(n+1, 1);
  iota(p.begin(), p.end(), 0);
}
int F(int u){
   if(u==p[u]) return u;
   return F(p[u]);
}
int Join(int u, int v, int tm){
  u= F(u) , v = F(v);
  if(u^v){
    if(rnk[u]<rnk[v]) swap(u, v);
    p[v] = u;
    rnk[u]+=rnk[v];
    t[v] = tm;
    return 1;
  }
  return 0;
}
int D(int u){
  if(dis[u]>=0) return dis[u];
  if(u==p[u]) return dis[u] = 0;
   return dis[u] = D(p[u])+1;
}

void solve() {
     int n, m;
     cin >> n >> m;
     int u, v, w;
     edges.resize(m);
     int i=0;
     for(auto &x: edges){
        cin >> u >> v >> w;
        x = {w, u, v, i++};

     }
     i=0;
     sort(edges.begin(), edges.end());
     init(n);
     for(auto &x: edges){
        tie(w, u, v, ignore) = x;
        if(Join(u, v, i++)) get<3>(x) = -1;
     }
     for(int i=1; i<=n; i++) D(i);
     vector<int> res(m, -1);
     int y;

     for(auto &x: edges){
        tie(w, u, v, y) = x;
         if(y==-1) continue;
        int mn =0;
        int it =0;
        while(u^v){
                it++;
            if(dis[u]>dis[v]) swap(u, v);
            mn = max(mn, t[v]);
            v = p[v];
//            if(it>4) assert(0);
        }
        res[y] = get<0>(edges[mn]);
     }
     for(int i=0; i<m; i++){
        if(res[i]>=0) cout << res[i]<<"\n";
     }

}


int32_t main()  {

//    ios_base::sync_with_stdio(0);
//    cin.tie(0);
    int tc, t=1;
//    cout << setprecision(10)<<fixed;
//    for(cin >> tc, t = 1; t<=tc; t++)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
//        cout << "Case "<<t<<": ";
        solve();
    }
    return 0;
}
/*
a
z
q
!
~
`
*/
