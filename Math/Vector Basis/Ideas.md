### Add two vector basis need O(bit<sup>2</sup>)
When use segment tree, it needs O(bit<sup>3</sup>) in per query.

# Problem
[Ivan and Burgers](https://codeforces.com/contest/1100/problem/F)   -> 
[Solution](https://codeforces.com/blog/entry/64543?#comment-484920) <br>
computes suffix/prefix when dividing [l, mid) [mid, r) (to add a number to a prefix/suffix is O(bits) time) and
then solves the queries with $l <= mid$ and $r >= mid$ in O(bits<sup>2</sup>) <br>
[Others Solution](https://codeforces.com/blog/entry/64495?#comment-484728)<br>
[Main soltuions](https://codeforces.com/blog/entry/64543?#comment-484920)<br>
[Form L to Right side First ![O(bits)](https://latex.codecogs.com/svg.latex?O(\text{bits})) different bits](https://codeforces.com/contest/1100/submission/48404972)

# Solution Code

```cpp
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    
    vector<int> basis(20), basis_index(20, 20); // closet index from L to right side.
    vector<vector<int>> basises(n), basises_indexed(n);
    
    for (int j = n - 1; j >= 0; j--) {
        int x = vec[j], indexed = j;
        for (int i = 19; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (basis[i] == 0) {
                    basis[i] = x;
                    basis_index[i] = indexed;
                    break;
                }
                if (indexed < basis_index[i]) {
                    swap(indexed, basis_index[i]);
                    swap(x, basis[i]);
                }
                x ^= basis[i];
            }
        }
        basises[j] = basis;
        basises_indexed[j] = basis_index;
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int res = 0;
        for (int i = 19; i >= 0; i--) {
            if (basises[l][i]) {
                if (basises_indexed[l][i] <= r) {
                    res = max(res, res ^ basises[l][i]);
                }
            }
        }
        cout << res << "\n";
    }

    return 0;
}

      
