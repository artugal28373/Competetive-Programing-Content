# String compression

## Z algorithm
Given a string  
$s$  of length  
$n$ . Find its shortest "compressed" representation, that is: find a string  
$t$  of shortest length such that  
$s$  can be represented as a concatenation of one or more copies of  
$t$ .

A solution is: compute the Z-function of  
$s$ , loop through all  
$i$  such that  
$i$  divides  
$n$ . Stop at the first  
$i$  such that  
$i + z[i] = n$ . Then, the string  
$s$  can be compressed to the length  
$i$ .


## KMP algorithm

Given a string  
$s$  of length  
$n$ . We want to find the shortest "compressed" representation of the string, i.e. we want to find a string  
$t$  of smallest length such that  
$s$  can be represented as a concatenation of one or more copies of  
$t$ .

It is clear, that we only need to find the length of  
$t$ . Knowing the length, the answer to the problem will be the prefix of  
$s$  with this length.

Let us compute the prefix function for  
$s$ . Using the last value of it we define the value  
$k = n - \pi[n - 1]$ . We will show, that if  
$k$  divides  
$n$ , then  
$k$  will be the answer, otherwise there is no effective compression and the answer is  
$n$ .

Let  
$n$  be divisible by  
$k$ . Then the string can be partitioned into blocks of the length  
$k$ . By definition of the prefix function, the prefix of length  
$n - k$  will be equal with its suffix. But this means that the last block is equal to the block before. And the block before has to be equal to the block before it. And so on. As a result, it turns out that all blocks are equal, therefore we can compress the string  
$s$  to length  
$k$ .

Of course we still need to show that this is actually the optimum. Indeed, if there was a smaller compression than  
$k$ , than the prefix function at the end would be greater than  
$n - k$ . Therefore  
$k$  is really the answer.

Now let us assume that  
$n$  is not divisible by  
$k$ . We show that this implies that the length of the answer is  
$n$ . We prove it by contradiction. Assuming there exists an answer, and the compression has length  
$p$  ( 
$p$  divides  
$n$ ). Then the last value of the prefix function has to be greater than  
$n - p$ , i.e. the suffix will partially cover the first block. Now consider the second block of the string. Since the prefix is equal with the suffix, and both the prefix and the suffix cover this block and their displacement relative to each other  
$k$  does not divide the block length  
$p$  (otherwise  
$k$  divides  
$n$ ), then all the characters of the block have to be identical. But then the string consists of only one character repeated over and over, hence we can compress it to a string of size  
$1$ , which gives  
$k = 1$ , and  
$k$  divides  
$n$ . Contradiction.

