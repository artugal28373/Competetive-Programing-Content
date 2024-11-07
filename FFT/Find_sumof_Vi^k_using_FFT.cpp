//https://www.codechef.com/viewsolution/1104897506


#include<bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace __gnu_pbds;
using namespace std;

#define pii pair<int, int>
#define int long long


template<class T>
using ordered_set = tree<int,null_type,less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

//mt19937_64 rnd_64(chrono::steady_clock::now().time_since_epoch().count());
//mt19937 rnd_32(chrono::steady_clock::now().time_since_epoch().count());


int bigmod(int b, int p, int mod) {
    b=b%mod;
    int res = 1;
    for(; p; res=(p&1?(1ll*res*b)%mod:res),b=(1ll*b*b)%mod, p/=2);
//    for(; p; res=(p&1?(1ll*res*b):res),b=(1ll*b*b), p/=2);
    return res;
}


void solve();
void preCompute();
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    string output = string("output") + ".txt";
//    string input = string("cottontail_climb_part_1_input")+".txt";
//    freopen(output.c_str(), "w", stdout);
//    freopen(input.c_str(), "r", stdin);
    int t= 0, tc=1;
    preCompute();
//    cin >> tc;

//    cout << fixed << setprecision(10);
    while(tc--) {
//        cout << "Case #"<<++t<<": ";
        solve();
    }
    return 0;
}
// https://codeforces.com/blog/entry/131567
int tc = 0;
const int mxn = 2e5+5;
const int mod =  998244353;
//const int mod =  1e9+7;
const int inf = (1ll<<30);
int add(int a, int b) {
    return (a+b>=mod? a+b-mod:(a+b<0? a+b+mod : a+b));
}


struct base {
    double x, y;
    base() {
        x = y = 0;
    }
    base(double x, double y): x(x), y(y) { }
};
inline base operator + (base a, base b) {
    return base(a.x + b.x, a.y + b.y);
}
inline base operator - (base a, base b) {
    return base(a.x - b.x, a.y - b.y);
}
inline base operator * (base a, base b) {
    return base(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
inline base conj(base a) {
    return base(a.x, -a.y);
}
int lim = 1;
vector<base> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};
const double PI = acosl(- 1.0);
void ensure_base(int p) {
    if(p <= lim) return;
    rev.resize(1 << p);
    for(int i = 0; i < (1 << p); i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1)  <<  (p - 1));
    roots.resize(1 << p);
    while(lim < p) {
        double angle = 2 * PI / (1 << (lim + 1));
        for(int i = 1 << (lim - 1); i < (1 << lim); i++) {
            roots[i << 1] = roots[i];
            double angle_i = angle * (2 * i + 1 - (1 << lim));
            roots[(i << 1) + 1] = base(cos(angle_i), sin(angle_i));
        }
        lim++;
    }
}
void fft(vector<base> &a, int n = -1) {
    if(n == -1) n = a.size();
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = lim - zeros;
    for(int i = 0; i < n; i++) if(i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
    for(int k = 1; k < n; k <<= 1) {
        for(int i = 0; i < n; i += 2 * k) {
            for(int j = 0; j < k; j++) {
                base z = a[i + j + k] * roots[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
        }
    }
}
//eq = 0: 4 FFTs in total
//eq = 1: 3 FFTs in total
// eq = equal
vector<int> multiply(vector<int> &a, vector<int> &b, int eq = 0) {
    int need = a.size() + b.size() - 1;
    int p = 0;
    while((1 << p) < need) p++;
    ensure_base(p);
    int sz = 1 << p;
    vector<base> A, B;
    if(sz > (int)A.size()) A.resize(sz);
    for(int i = 0; i < (int)a.size(); i++) {
        int x = (a[i] % mod + mod) % mod;
        A[i] = base(x & ((1 << 15) - 1), x >> 15);
    }
    fill(A.begin() + a.size(), A.begin() + sz, base{0, 0});
    fft(A, sz);
    if(sz > (int)B.size()) B.resize(sz);
    if(eq) copy(A.begin(), A.begin() + sz, B.begin());
    else {
        for(int i = 0; i < (int)b.size(); i++) {
            int x = (b[i] % mod + mod) % mod;
            B[i] = base(x & ((1 << 15) - 1), x >> 15);
        }
        fill(B.begin() + b.size(), B.begin() + sz, base{0, 0});
        fft(B, sz);
    }
    double ratio = 0.25 / sz;
    base r2(0,  - 1), r3(ratio, 0), r4(0,  - ratio), r5(0, 1);
    for(int i = 0; i <= (sz >> 1); i++) {
        int j = (sz - i) & (sz - 1);
        base a1 = (A[i] + conj(A[j])), a2 = (A[i] - conj(A[j])) * r2;
        base b1 = (B[i] + conj(B[j])) * r3, b2 = (B[i] - conj(B[j])) * r4;
        if(i != j) {
            base c1 = (A[j] + conj(A[i])), c2 = (A[j] - conj(A[i])) * r2;
            base d1 = (B[j] + conj(B[i])) * r3, d2 = (B[j] - conj(B[i])) * r4;
            A[i] = c1 * d1 + c2 * d2 * r5;
            B[i] = c1 * d2 + c2 * d1;
        }
        A[j] = a1 * b1 + a2 * b2 * r5;
        B[j] = a1 * b2 + a2 * b1;
    }
    fft(A, sz);
    fft(B, sz);
    vector<int> res(need);
    for(int i = 0; i < need; i++) {
        long long aa = A[i].x + 0.5;
        long long bb = B[i].x + 0.5;
        long long cc = A[i].y + 0.5;
        res[i] = (aa + ((bb % mod) << 15) + ((cc % mod) << 30))%mod;
    }
    return res;
}


vector<int> dp[101][101];
bool vis[101][101];
int c[101], v[101];
int f[2001];
int fi[2001];
int s, n, k;

vector<int> go(int pos, int s) {
    if(pos==0) {
        vector<int> temp(k+1, 0);
        temp[0]=1;
        return temp;
    }
    if(vis[pos][s]) return dp[pos][s];
    vis[pos][s] = 1;
    dp[pos][s] = go(pos-1, s);
    if(s - c[pos]>=0) {
        vector<int> temp = go(pos-1, s-c[pos]);// sum of previous result res ^ 0, 1, 2, 3, ..k... temp2[0] = a^0+b^0+c^0... , temp2[1]= a^1+b^1+c^1....
        vector<int> temp2 (k+1, 0);// contain v[pos] ^ 0, 1, 2, ..., k
        int w = 1;
        // result will be
        // d ^ k = (i+j)!/i!/j! * a^i * b^j where i+j==k
        // d^k /(i+j)! =  a^i/i! * b^j/j! where i+j==k
        for(int i=0; i<=k; i++) {
            temp2[i] = (w*fi[i])%mod;
            temp[i]  =(temp[i] * fi[i])%mod;
            w = (w * v[pos])%mod;
        }
        vector<int> res = multiply(temp2, temp);// d^k/k! = d^k/(i+j)!;
        res.resize(k+1);
        for(int i=0; i<=k; i++) res[i] = (res[i] * f[i])%mod; // d^k = d^k /k! *k!
        for(int i=0; i<=k; i++) dp[pos][s][i] = (dp[pos][s][i]+res[i])%mod;
    }
//    cout << pos << " * "<<s << endl;
    return dp[pos][s];

}

void solve() {
    cin >> n >> s >> k;
    for(int i=1; i<=n; i++) {
        cin >> c[i] >> v[i];
    }
    f[0] = 1;
    for(int i=1; i<=k; i++) f[i] = (f[i-1]*i)%mod;
    for(int i=0; i<=k; i++) {
//        fi[i] = mod - ((mod/i) * fi[mod%i])%mod;
          fi[i] = bigmod(f[i], mod-2, mod);
    }
    cout << go(n, s)[k];

}


void preCompute() {

//   f[0]=1;
//   for(int i=1; i<mxn; i++) f[i] = (f[i-1]*i)%mod;
//   fi[1]=1;
//   for(int i=2; i<mxn; i++){
//     fi[i] = mod - ( (mod/i) * fi[mod%i] )%mod;
//   }
//   for(int i=2; i<mxn; i++) fi[i] = (fi[i-1]*fi[i])%mod;

}
