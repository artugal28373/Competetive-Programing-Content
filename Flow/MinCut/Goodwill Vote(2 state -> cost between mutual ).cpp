//2 state -> cost between mutual 
/*
                           -------- sleep--------
                          /                       \
                        /cost to switch opposite   \type1
                      /                             \
                    f1-------bidirectionl edge------ f2
                     |       cost for opp^ositon      |type 2
                     |    cost for oppositon          |
                    f3                               f4
                      \   cost to switch opposite    /type 1
                          notsleep------------------

  type 1 = cost for switch ..cut this min the node get opposite side
  type 2 = cost for opposition betwwen two mutual. cut thi min we accept the opposition between two mutual.

*/
// problem link : https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2057
// problem sol:

// problem link: https://vjudge.net/contest/586189#problem/N
// problem sol: https://vjudge.net/solution/47216264/uRe2FxsixbO9My6E0e8H
