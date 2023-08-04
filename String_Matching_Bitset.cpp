// https://codeforces.com/contest/963/submission/205448733

#include <bits/stdc++.h>
using namespace std ;
const int N = 1e5 + 5 ;
char S[N] , T[N];
bitset <N> F[26] , P;

int main () {
    scanf("%s" , S) ;
    int n = strlen(S) ;
    for (int i = 0 ; i < n ; i++) {
        F[S[i]-'a'][i] = 1 ;
    }
    int Q ; scanf("%d",&Q) ;
    while (Q--) {
        int k ; scanf("%d %s" , &k , &T) ;
        P.set() ; int m = strlen(T) ;
        for (int i = 0 ; i < m ; i++) {
            P &= (F[T[i]-'a']>>i) ;
        }
        vector <int> Pos ;
        for (int i = P._Find_first() ; i < n ; i = P._Find_next(i)) {
            Pos.emplace_back(i) ;
        }
        if (Pos.size() < k) {
            printf ("-1\n") ;
        }
        else {
            int ans = 1e9 ;
            for(int i = k-1 ; i < Pos.size() ; i++) {
                ans = min(ans,Pos[i]-Pos[i-k+1]) ;
            }
            printf ("%d\n" , ans+m) ;
        }
    }
}
