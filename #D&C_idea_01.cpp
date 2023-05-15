// https://atcoder.jp/contests/agc002/tasks/agc002_d
// div & con idea


#include <iostream>
#include <cstdio>

#define maxn 100005
#define pii pair <int, int>
#define mp make_pair
#define fi first
#define se second 

using namespace std;

inline int read(){
	int x = 0, flag = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') flag = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
	return x * flag;
}

int n, m, Q, f[maxn], siz[maxn], b[maxn], bb[maxn], dep[maxn];
pii e[maxn], s[maxn];

//pii getf(int x){ //fa dep
//	if(x == f[x]) return mp(x, 0);
//	pii re = getf(f[x]);
//	return mp(re.fi, re.se + 1);
//}

int getf(int x){
	while(x != f[x]) x = f[x];
	return x;
}

struct que{
	int x, y, z, ans;
}q[maxn];

int now = 0;

void erfen(int l, int r, int bl, int br){
//	cout<<' '<<l<<' '<<r<<endl;
//	for(int i = bl; i <= br; ++i) cout << b[i] << ' ';
//	puts("");
	int mid = (l + r) >> 1;
	while(now < mid){
		++now;
		int fu = getf(e[now].fi), fv = getf(e[now].se);
		if(fu != fv){
//			if(fu.se > fv.se) swap(fu, fv);
			if(dep[fu] > dep[fv]) swap(fu, fv);
			s[now] = mp(fu, fv);
			f[fu] = fv;
			siz[fv] += siz[fu];
			dep[fv] = max(dep[fv], dep[fu] + 1);
		}else s[now] = mp(0, 0);
	}
	while(now > mid){
		int u = s[now].fi, v = s[now].se;
		if(u){
			siz[v] -= siz[u];
			f[u] = u;
		}
		--now;
	}
//	cout<<"mid = "<<mid<<endl;
//	for(int i = 1; i <= n; ++i) cout << siz[getf(i).fi]<<' ';
//	puts("");
	if(l == r){
		for(int i = bl; i <= br; ++i) q[b[i]].ans = l;
		return;
	}
	int numl = bl - 1, numr = 0;
	for(int I = bl; I <= br; ++I){
		int i = b[I];
		int fx = getf(q[i].x), fy = getf(q[i].y);
		if(fx == fy){
			if(siz[fx] >= q[i].z) b[++numl] = i;
			else bb[++numr] = i;
		}else{
			if(siz[fx] + siz[fy] >= q[i].z) b[++numl] = i;
			else bb[++numr] = i;
		}
	}
//	for(int i = bl; i <= numl; ++i) cout << b[i] << ' ';
//	for(int i = 1; i <= numr; ++i) cout << bb[i] << ' ';
//	puts("");
//	for(int i = 1; i <= numr; ++i) b[i + numl] = bb[i];
	for(int i = numl + 1; i <= br; ++i) b[i] = bb[i - numl];
//	for(int i = bl; i <= br; ++i) cout << b[i] << ' ';
//	puts("");
	erfen(l, mid, bl, numl);
	erfen(mid + 1, r, numl + 1, br);
	return;
}

int main(){
//	freopen("in.in", "r", stdin);
//	freopen("out.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) f[i] = i, siz[i] = 1;
	for(int i = 1; i <= m; ++i) e[i].fi = read(), e[i].se = read(); 
	Q = read();
	for(int i = 1; i <= Q; ++i) q[i].x = read(), q[i].y = read(), q[i].z = read(), b[i] = i;
	erfen(1, m, 1, Q);
	for(int i = 1; i <= Q; ++i) printf("%d\n", q[i].ans);
	return 0; 
}
/*
1
2
3
1
5
5

*/
