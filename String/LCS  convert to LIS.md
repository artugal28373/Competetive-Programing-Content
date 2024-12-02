[LCS problem solve using LIS](https://codeforces.com/gym/104349/submission/294341909)<br><br>
For example if you have string "abacba" you have these lists

'a': 5,2,0

'b': 4, 1

'c': 3

Now, if you look at S2 and for each character put in a sequence its list(note that it can be empty), you have a sequence in which you should search for LIS. Here's with the example if S2 is 'baaxac' you have sequence 

'b': 4, 1

'a': 5,2,0

'a': 5,2,0

'x': 

'a': 5,2,0

'c': 3

The LIS of this sequence is 3 as the answer would be
