### Add two vector basis need O(bit<sup>2</sup>)
When use segment tree, it needs O(bit<sup>3</sup>) in per query.

# Problem
[Ivan and Burgers](https://codeforces.com/contest/1100/problem/F)   -> 
[Solution](https://codeforces.com/blog/entry/64543?#comment-484920) <br>
computes suffix/prefix when dividing [l, mid) [mid, r) (to add a number to a prefix/suffix is O(bits) time) and
then solves the queries with $l <= mid$ and $r >= mid$ in O(bits<sup>2</sup>) <br>
[Others Solution](https://codeforces.com/blog/entry/64495?#comment-484728)<br>
[Main soltuions](https://codeforces.com/blog/entry/64543?#comment-484920)
