// https://codeforces.com/problemset/problem/1257/G
// number of way construct divisor of x such that each one have (total number of prime+1)/2 prime numbers.  

const int N = 3e6+5;
int cnt[N];
int n, k;
vector<int> dc(int l, int r) {
    if(l==r) {
        vector<int> temp(cnt[l]+1, 1);
        return temp;
    }
    int m = (l+r)/2;
    vector<int> a=dc(l, m);
    vector<int> b=dc(m+1, r);
    if(a.size()==1) return b;
    if(b.size()==1) return a;
    vector<int> temp = multiply(a, b);
    if(temp.size()>n+1) temp.resize(n+1);
    return temp;
}
void solve() {
    cin >> n;
    for(int i=1; i<=n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }
    vector<int>temp = dc(0, 3e6);
    int mx = (n+1)/2;
//    for(int &x: temp) cout << x<< " ";
    cout << temp[mx] << "\n";
}
