/*

same number multiple time.

for(int i=0; i<=k; i++){
    int num = K[i]; // num to be proccessed
    int amount = count[num];// num has amount times
    int temp = 1;
    // 1, 2, 4, 8, ....., (2^k) such that 2*(k+1)-1 <= amount
    // 1, 2, 4, 8, ....., 2^k can represent 2^(k+1)-1  
    while(temp <= amount){
         amount -= temp;
         for(int j = mx; j>=temp*num; j--)
             dp[j] |= dp[j-temp*num];
    }
    if(amount >0 ){
    // here amount < 2^(k+1) - 1
    
    // if the number is grater than 2^(k+1) that is optimal for global result ,let X, then
    //  amount + (X-amount)
    // ammount is added below and (X-amount) is add before as a bit sequence
        temp = amount;
         for(int j = mx; j>=temp*num; j--)
             dp[j] |= dp[j-temp*num];
    }
}

// time complexity O(S*N*log(a)), a = max(count[]).

*/
