!! If you haven't tried the problem, don't look at the solution !!

Link to problem: https://www.hackerrank.com/contests/projecteuler/challenges/euler221/problem?isFullScreen=true
Use AlexTest2500000.txt contains list of first 2.5M Alexandrian Integers. You can use it for your testing




This solution is based on a fact that 
any prime odd P | N^2+1, should be in the form 1 mod 4, 
and set of all odd primes and 2, can be witten as sum of two squares That is there exists a,b in Z such that a^2 + b^2 = P (2 = 1 + 1 , 5 = 2^2+ 1, 13 = 2^2 + 3^2..)
and (a^2+b^2)(c^2+d^2) = (ac+bd)^2 + (ad-bc)^2, meaning that any product of such primes is also sum of two squares
In this equation we set (ac+bd) = N and (ad-bc) = 1( => gcd(a,b) = 1)
so , if we fix a,b then we can find c,d satisfying (ad-bc) = 1, for each (a,b,c,d), we have generated a solution for D | N^2 +1 , we use this fact to generate all possible numbers of form (N)(N+D)(N+(N^2+1)/D) upto certain limit. 
We use some clever techniques to minimize to search limit in each iteration for a,b. 