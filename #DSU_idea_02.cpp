// https://atcoder.jp/contests/agc002/tasks/agc002_d

#include<bits/stdc++.h>

using namespace std;

const int mxn = (1e5)+5;
vector<int> p, sx,beingf[mxn],childof[mxn], beingc[mxn],sixeof[mxn], fatherof[mxn];
int n;
void DSU(int _n) {
    n = _n;
    p = vector<int>(_n+2, 0);
    sx = vector<int>(_n+2, 1);
    for(int i=1; i<=_n; i++) p[i] = i;
    for(int i=1; i<=n; i++) {
        beingf[i].push_back(0);
        childof[i].push_back(i);
        fatherof[i].push_back(i);
        beingc[i].push_back(0);
        sixeof[i].push_back(1);
        sx[i] = 1;
    }
}
int f(int c) {
    if(c==p[c]) return c;
    return p[c] = f(p[c]);
}
int cl(int f, int t) {
   return sixeof[f][upper_bound(beingf[f].begin(), beingf[f].end(), t) - beingf[f].begin()-1];
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m;
    cin >> n >> m;
    DSU(n);
    for(int i=1; i<=m; i++) {
        int u, v;
        cin >> u >> v;
        int c = f(u), d = f(v);
        if(c==d) continue;
        if(sx[c]<sx[d]) swap(c, d);
        p[d] = c;
        sx[c] = sx[c]+sx[d];
        beingf[c].push_back(i);
        sixeof[c].push_back(sx[c]);
        for(int j=0; j<childof[d].size(); j++){
            int e = childof[d][j];
            childof[c].push_back(e);
            beingc[e].push_back(i);
            fatherof[e].push_back(c);
        }
        childof[d].clear();
    }
    int p;
    cin >> p;
    while(p--){
        int x, y, w;
        cin >> x >> y >> w;
        int l = 1, h = m;
        int res = 0;

        while(l<=h){
            int m = (l+h)/2;
            int xf = fatherof[x][upper_bound(beingc[x].begin(), beingc[x].end(), m ) - beingc[x].begin() - 1];
            int yf = fatherof[y][upper_bound(beingc[y].begin(), beingc[y].end(), m ) - beingc[y].begin() - 1];
            int tot = cl(xf, m);
            if(xf^yf) tot = tot + cl(yf, m);
            if(tot >= w) res = m, h = m-1;
            else l = m+1;
        }
        cout << res<<"\n";
    }

}
/// skaib vai
///** 
#include<bits/stdc++.h>
#define xx first
#define yy second
#define mxn 100005
#define push_back emplace_back
using namespace std;
vector<int>e1[mxn], comp[mxn], e2[mxn], sz[mxn], vec[mxn];
int par[mxn], ss[mxn];
int union_find(int x)
{
    if(x==par[x])return x;
    else return par[x]= union_find(par[x]);
}
int func(int c, int m)
{
    return sz[c][ upper_bound(e2[c].begin(), e2[c].end(), m)-e2[c].begin()-1 ];
}
int main()
{
    int n, m, x, y, z;
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; i++)par[i]= i;
    for(int i=1; i<=n; i++)
    e1[i].push_back(0), comp[i].push_back(i), vec[i].push_back(i),
    e2[i].push_back(0), sz[i].push_back(1), ss[i]= 1;
    for(int i=1; i<=m; i++)
    {
        scanf("%d %d", &x, &y);
        int a= union_find(x);
        int b= union_find(y);
        if(a!=b)
        {
            if(ss[a]<ss[b])swap(a, b), swap(x, y);
            par[b]= a;
            e2[a].push_back(i);
            ss[a]+= ss[b];
            sz[a].push_back(ss[a]);
            for(int j=0; j<vec[b].size(); j++)
            {
                z= vec[b][j];
                vec[a].push_back(z);
                e1[z].push_back(i);
                comp[z].push_back(a);
            }vec[b].clear();
        }
    }
    int q;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d %d %d", &x, &y, &z);
        int lo= 1, hi= m, res;
        while(lo<=hi)
        {
            int mid= (lo+hi)/2;
            int cx= comp[x][ upper_bound(e1[x].begin(), e1[x].end(), mid)-e1[x].begin()-1 ];
            int cy= comp[y][ upper_bound(e1[y].begin(), e1[y].end(), mid)-e1[y].begin()-1 ];
            int tot= func(cx, mid);
            if(cx!=cy)tot+= func(cy, mid);
            if(tot>=z)res= mid, hi= mid-1;
            else lo= mid+1;
        }
        printf("%d\n", res);
    }
    return 0;
}

**//
