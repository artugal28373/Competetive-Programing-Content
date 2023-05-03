/*
https://codeforces.com/gym/100570/problem/F
*/
#include<bits/stdc++.h>
using namespace std;
const int mxn = 2*100000+5;
////#include<ext/pb_ds/tree_policy.hpp>
////#include<ext/pb_ds/assoc_container.hpp>
////using namespace __gnu_pbds;
////*find_by_order(x)=kth number counting from 0**//**order_of_key(x)=number of element less than x*
////template<typename temp>
////using ordered_set = tree<temp, null_type, less_equal<temp>, rb_tree_tag,tree_order_statistics_node_update>;
////ordered_set<int> st[4*mxn];
#define int long long int
using pii = pair<int, int>;
vector<pii> v[mxn];
int vis[mxn],parent[mxn],subsz[mxn];

/**********************************/
int dis[mxn][20],level[mxn], n;
vector<vector<int>> dp(mxn, vector<int>()), sub(mxn, vector<int>());
void dfsp(int u, int pr,  int w, int clev, int c) {
    dis[u][clev] = w;
    dp[c].push_back(w); // own
//    cout << c <<" "<<u<<" ** "<<w<<endl;
    for(pii &x: v[u]) {
        if(x.first==pr || vis[x.first]) continue;
        dfsp(x.first, u, w+x.second, clev, c);
    }
}
void dfspp(int u, int pr,  int w, int clev, int c) {
//    cout << c <<" "<<u<<" && "<<w<<endl;
    assert(dis[u][clev]==w); 
    sub[c].push_back(w); // sub
    for(pii &x: v[u]) {
        if(x.first==pr || vis[x.first]) continue;
        dfspp(x.first, u, w+x.second, clev, c);
    }
}

int _find(int u, int l) {
    int res = upper_bound(dp[u].begin(), dp[u].end(), l) - dp[u].begin();
    int v = u;
    while(parent[u]) {
        int pp = parent[u];
        int w = dis[v][level[pp]];
        if(l>=w) {
            res+=upper_bound(dp[pp].begin(), dp[pp].end(), l-w) - dp[pp].begin(); 
            res-=upper_bound(sub[u].begin(), sub[u].end(), l-w) - sub[u].begin();
        }
        u = parent[u];
    }
    return res;
}
// a
/**  Centroid Decomposition **/
void findsize(int node, int par) {
    subsz[node] = 1;
    for(pii &x: v[node]) {
        if(x.first==par || vis[x.first]) continue;
        findsize(x.first, node);
        subsz[node]+=subsz[x.first];
    }
}
int val;
int findcentroid(int node, int par) {
    for(pii &x: v[node]) {
        if(x.first==par || vis[x.first] || subsz[x.first]*2<=val) continue;
        return findcentroid(x.first,node);
    }
    return node;
}
int centroidDecomposition(int node, int par) {
    findsize(node, 0);
    val = subsz[node];
    int c = findcentroid(node, 0);
    parent[c] = par;
    vis[c] = 1;
    level[c] = level[par]+1; // lg n
    dfsp(c, c, 0, level[c], c);
    sort(dp[c].begin(), dp[c].end()); // for centroid
    for(pii&x: v[c]) {
        if(vis[x.first]) continue;
        int r = centroidDecomposition(x.first, c); 
        dfspp(x.first, c, x.second, level[c], r); // for centroid subtree
        sort(sub[r].begin(), sub[r].end());
    }
    vis[c] = 0;
    return c;
}
/**  End Centroid Decomposition **/
int32_t main() {
    //  a
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int p;
    cin >> n >> p;
    for(int i= 2;  i<=n; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        v[a].push_back({b, w});
        v[b].push_back({a, w});
    }
    centroidDecomposition(1, 0);
    while(p--) {
        int v, l;
        cin >> v >> l;
        cout << _find(v, l)<<"\n";
    }
    return 0;
}

