#include <stdio.h>
#include "proj09.support.h"

int main()
{
	
	printf("\nNegate Positive Bef: %d After: %d\n", 40, negate(40));
	printf("\nNegate Negative Bef: %d After: %d\n", -40, negate(-40));
	
	printf("\nAbsolute Positive Bef: %d After: %d\n", 50, absolute(50));
	printf("\nAbsolute Negative Bef: %d After: %d\n", -50, absolute(-50));
	
	printf("\nAdd 1: %d + %d = %d\n", 20, 30, add(20, 30));
	printf("\nAdd 2: %d + %d = %d\n", 20, -20, add(20, -20));
	printf("\nAdd 3: %d + %d = %d\n", -33, -20, add(-33, -20));
	printf("\nAdd 4: %d + %d = %d\n", 20, 0, add(20, 0));
	printf("\nAdd 5: %d + %d = %d\n", -45, 0, add(-45, 0));
	printf("\nAdd 6: %d + %d = %d\n", 0, 0, add(0, 0));
	
	printf("\nSub 1: %d - %d = %d\n", 5, 2, sub(5, 2));	
	printf("\nSub 2: %d - %d = %d\n", 5, -2, sub(5, -2));	
	printf("\nSub 3: %d - %d = %d\n", -5, -2, sub(-5, -2));	
	printf("\nSub 4: %d - %d = %d\n", 50, 0, sub(50, 0));	
	printf("\nSub 5: %d - %d = %d\n", 0, -50, sub(0, -50));	
	printf("\nSub 6: %d - %d = %d\n", 0, 50, sub(0, 50));
	
	printf("\nMul 1: %d * %d = %d\n", 1, 2, mul(1,2));	
	printf("\nMul 2: %d * %d = %d\n", 1, -2, mul(1,-2));	
	printf("\nMul 3: %d * %d = %d\n", -1, -2, mul(-1,-2));	
	printf("\nMul 4: %d * %d = %d\n", 5, 7, mul(5,7));	
	printf("\nMul 5: %d * %d = %d\n", 100, 2343, mul(100,2343));
	
	printf("\nDiv 1: %d / %d = %d\n", 9, 3, divide( 9, 3));
	printf("\nDiv 2: %d / %d = %d\n", 24, -6, divide( 24, -6));
	printf("\nDiv 3: %d / %d = %d\n", 24, 0, divide( 24, 0));
	printf("\nDiv 4: %d / %d = %d\n", 5, 5, divide( 5, 5));
	printf("\nDiv 5: %d / %d = %d\n", 0, 5, divide( 0, 5));
	
	printf("\nPower 1: %d ^ %d = %d\n", 1, 1, power( 1, 1));	
	printf("\nPower 2: %d ^ %d = %d\n", 2, 2, power( 2, 2));	
	printf("\nPower 3: %d ^ %d = %d\n", 5, 10, power( 5, 10));	
	printf("\nPower 4: %d ^ %d = %d\n", 891, 0, power( 891, 0));	
	printf("\nPower 5: %d ^ %d = %d\n", 1, -11, power( 1, -11));
	
	printf("\nFactorial 1: %d! = %d\n", 0, factorial(0));
	printf("\nFactorial 2: %d! = %d\n", -4, factorial(-4));
	printf("\nFactorial 3: %d! = %d\n", 6, factorial(6));
}
