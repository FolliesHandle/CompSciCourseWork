/************************
* Dominic Mazza
* 12-3-2020
* Project 10
* proj10.driver.c
************************/
#include <stdio.h>
#include "/user/cse320/Projects/project10.support.h"

int main()
{
	char ch_arr1 [20] = "flabbergasted";
	printf("\nWord: %s Len: %d\n", ch_arr1, length(ch_arr1));
	char ch_arr2 [] = "banana";
	printf("\nWord: %s Len: %d\n", ch_arr2, length(ch_arr2));
	char ch_arr3 [50] = "";
	printf("\nWord: %s Len: %d\n", ch_arr3, length(ch_arr3));
	char ch_arr4 []= "ten";
	printf("\nWord: %s Len: %d\n", ch_arr4, length(ch_arr4));
		
	printf("\nWord: %s Destination Pre: %s\n", ch_arr1, ch_arr3);
	copy(ch_arr3, ch_arr1);
	printf("\nWord: %s Destination Post: %s\n", ch_arr1, ch_arr3);

	printf("\nWords to be combined: %s, %s\n", ch_arr1, ch_arr2);
	append(ch_arr1, ch_arr2);
	printf("\nCombined: %s\n", ch_arr1);
	
	printf("\nOriginal: %s Duplicate: %s\n", ch_arr4, duplicate(ch_arr4));
	
	printf("\n %s compared with %s results in %d\n", ch_arr1, ch_arr4, compare(ch_arr1, ch_arr4));
	char ch_arr5 [50] = "hello";
	char ch_arr6 [50] = "hello";
	printf("\n %s compared with %s results in %d\n", ch_arr5, ch_arr6, compare(ch_arr5, ch_arr6));
	
}
