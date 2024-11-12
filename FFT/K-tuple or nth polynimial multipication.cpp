// (1+x^i)*(1+x^j)*(1+x^k)*......*(1+x^n) -> n(log(n)^2)

// you need k-tuple then conside like either takes or not
// exm: (1+x^i)*(1+x^j)*(1+x^k)*......*(1+x^n)
// https://codeforces.com/problemset/problem/1218/E

#include<bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define int long long



void solve();
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
const int mxn = (1<<21);
const int mod =  (119<<23)+1;
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
int a[mxn], operating[mxn];
int n, k;
vector<int> dc(int l, int r) {
    if(l==r) {
        vector<int> temp= {1, operating[l]};
        return temp;
    }
    int m = (l+r)/2;
    vector<int> a=dc(l, m);
    vector<int> b=dc(m+1, r);
    vector<int> temp = multiply(a, b);
    if(temp.size()>k+1) temp.resize(k+1);
    return temp;
}
void solve() {
    cin >> n >> k;
    for(int i=0; i<n; i++) cin >> a[i];
    int q;
    cin >> q;
    while(q--) {
        int op;
        cin >> op;
        if(op==1) {
            int q, i, d;
            cin >> q >> i >> d;
            for(int i=0; i<n; i++) {
                operating[i] = a[i]%mod;
                operating[i] = (q - operating[i] +mod)%mod;
            }
            i--;
            operating[i] = d%mod;
            operating[i] = (q - operating[i] + mod)%mod;
        } else {
            int q, l, r, d;
            cin >> q >> l >> r >> d;
            l--, r--;
            for(int i=0; i<n; i++) {
                if(i<l || r<i) {
                    operating[i] = a[i]%mod;
                    operating[i] = (q - operating[i] + mod)%mod;
                } else {
                    operating[i] = (a[i]+d)%mod;
                    operating[i] = (q - operating[i]+mod)%mod;
                }
            }
        }
        cout << dc(0, n)[k]<<"\n";
    }
}


